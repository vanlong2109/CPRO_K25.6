/*
 * Logic điều khiển chính cho Smart Plant Watering System
 */
#include <stdio.h>
#include "spws_controller.h"
#include "../hal_library/hal_actuators.h"

static void start_pump(SystemState_t *state, uint32_t now_s, const char *reason)
{
    HAL_TurnPumpOn();
    state->pumpState = PUMP_ON;
    state->pumpStartedAt_s = now_s;
    if (reason != NULL)
    {
        printf("%s\n", reason);
    }
}

void SPWS_StopPump(SystemState_t *state, const char *reason)
{
    if (state->pumpState == PUMP_OFF)
    {
        return;
    }

    HAL_TurnPumpOff();
    state->pumpState = PUMP_OFF;
    state->autoWateringActive = false;
    state->manualWateringActive = false;

    if (reason != NULL)
    {
        printf("%s\n", reason);
    }
}

void SPWS_InitDefaults(SystemState_t *state, SystemSettings_t *settings, SensorData_t *sensorData)
{
    settings->minMoistureThreshold = DEFAULT_MIN_MOISTURE;
    settings->maxMoistureThreshold = DEFAULT_MAX_MOISTURE;
    settings->sensorReadInterval_s = DEFAULT_SENSOR_INTERVAL_SEC;
    settings->maxWateringDuration_s = DEFAULT_MAX_WATER_DURATION_SEC;
    settings->manualWateringDuration_s = DEFAULT_MANUAL_DURATION_SEC;

    state->mode = MODE_AUTO;
    state->pumpState = PUMP_OFF;
    state->ledState = LED_OFF;
    state->autoWateringActive = false;
    state->manualWateringActive = false;
    state->pumpStartedAt_s = 0;
    state->manualWaterStartedAt_s = 0;

    sensorData->soilMoisturePercent = 0.0f;
    sensorData->ambientTemperatureC = 0.0f;
    sensorData->lastReadTime_s = 0;
}

void SPWS_RunAutoMode(SystemState_t *state, const SystemSettings_t *settings, const SensorData_t *sensorData, uint32_t now_s)
{
    if (state->pumpState == PUMP_OFF)
    {
        if (sensorData->soilMoisturePercent < settings->minMoistureThreshold)
        {
            state->autoWateringActive = true;
            state->manualWateringActive = false;
            start_pump(state, now_s, "[AUTO] Dat kho, bat bom tu dong");
        }
    }
    else
    {
        bool moistureReached = sensorData->soilMoisturePercent > settings->maxMoistureThreshold;
        bool timeoutReached = (now_s - state->pumpStartedAt_s) >= settings->maxWateringDuration_s;

        if (moistureReached || timeoutReached)
        {
            if (moistureReached)
            {
                printf("[AUTO] Do am dat dat nguong %.1f%%, tat bom\n", sensorData->soilMoisturePercent);
            }
            else
            {
                printf("[AUTO] Qua thoi gian toi da %us, tat bom\n", settings->maxWateringDuration_s);
            }
            SPWS_StopPump(state, "[AUTO] Ket thuc chu ky tuoi tu dong");
        }
    }
}

void SPWS_RunManualMode(SystemState_t *state, const SystemSettings_t *settings, uint32_t now_s, bool manualPressed)
{
    if (manualPressed)
    {
        state->manualWateringActive = true;
        state->autoWateringActive = false;
        state->manualWaterStartedAt_s = now_s;
        start_pump(state, now_s, "[MANUAL] Nhan nut, bat bom tuoi thu cong");
    }

    if (state->manualWateringActive && state->pumpState == PUMP_ON)
    {
        bool durationExpired = (now_s - state->manualWaterStartedAt_s) >= settings->manualWateringDuration_s;
        if (durationExpired)
        {
            printf("[MANUAL] Het thoi gian tuoi thu cong, tat bom\n");
            SPWS_StopPump(state, "[MANUAL] Ket thuc chu ky tuoi thu cong");
        }
    }
}

void SPWS_ApplyOutputs(SystemState_t *state)
{
    LedState_t targetLed = LED_GREEN;
    if (state->pumpState == PUMP_ON)
    {
        targetLed = LED_YELLOW;
    }

    state->ledState = targetLed;
    HAL_SetLedState(targetLed);
}
