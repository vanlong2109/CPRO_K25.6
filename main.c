/*
 * Vòng lặp chính điều khiển hệ thống tưới cây thông minh
 */
#include <stdio.h>
#include <unistd.h>
#include "config.h"
#include "spws_controller/spws_controller.h"
#include "hal_library/hal_sensors.h"
#include "hal_library/hal_actuators.h"
#include "hal_library/hal_buttons.h"

static SystemState_t g_systemState;
static SystemSettings_t g_systemSettings;
static SensorData_t g_sensorData;

static void System_Init(void)
{
    HAL_Actuators_Init();
    HAL_Sensors_Init();
    HAL_Buttons_Init();

    SPWS_InitDefaults(&g_systemState, &g_systemSettings, &g_sensorData);
    SPWS_ApplyOutputs(&g_systemState);

    printf("[SYSTEM] Khoi dong SPWS - AUTO, bom OFF\n");
    printf("[SYSTEM] Cau hinh mac dinh: min=%.1f%%, max=%.1f%%, sensor=%us, auto_max=%us, manual=%us\n",
           g_systemSettings.minMoistureThreshold,
           g_systemSettings.maxMoistureThreshold,
           g_systemSettings.sensorReadInterval_s,
           g_systemSettings.maxWateringDuration_s,
           g_systemSettings.manualWateringDuration_s);
}

int main(void)
{
    System_Init();

    while (1)
    {
        uint32_t now_s = HAL_GetSystemTimeSeconds();

        if (HAL_Button_ModeTogglePressed(now_s))
        {
            if (g_systemState.mode == MODE_AUTO)
            {
                g_systemState.mode = MODE_MANUAL;
                SPWS_StopPump(&g_systemState, "[SYSTEM] Chuyen sang MANUAL, tat bom neu dang chay");
                printf("[SYSTEM] MODE -> MANUAL\n");
            }
            else
            {
                g_systemState.mode = MODE_AUTO;
                printf("[SYSTEM] MODE -> AUTO\n");
            }
        }

        bool manualPressed = false;
        if (g_systemState.mode == MODE_MANUAL)
        {
            manualPressed = HAL_Button_ManualWaterPressed(now_s);
        }

        if ((now_s - g_sensorData.lastReadTime_s) >= g_systemSettings.sensorReadInterval_s)
        {
            g_sensorData.soilMoisturePercent = HAL_ReadSoilMoisture();
            g_sensorData.ambientTemperatureC = HAL_ReadAmbientTemperature();
            g_sensorData.lastReadTime_s = now_s;

            printf("[SENSOR] t=%us | Do am=%.1f%% | Nhiet=%.1fC\n",
                   now_s,
                   g_sensorData.soilMoisturePercent,
                   g_sensorData.ambientTemperatureC);
        }

        if (g_systemState.mode == MODE_AUTO)
        {
            SPWS_RunAutoMode(&g_systemState, &g_systemSettings, &g_sensorData, now_s);
        }
        else
        {
            SPWS_RunManualMode(&g_systemState, &g_systemSettings, now_s, manualPressed);
        }

        SPWS_ApplyOutputs(&g_systemState);
        sleep(1);
    }

    return 0;
}
