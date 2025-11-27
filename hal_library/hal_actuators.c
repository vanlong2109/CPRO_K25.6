/*
 * Mô phỏng bộ chấp hành: bơm và LED trạng thái
 */
#include <stdio.h>
#include "hal_actuators.h"

static PumpState_t s_pumpState = PUMP_OFF;
static LedState_t s_ledState = LED_OFF;

void HAL_Actuators_Init(void)
{
    s_pumpState = PUMP_OFF;
    s_ledState = LED_OFF;
}

void HAL_TurnPumpOn(void)
{
    if (s_pumpState == PUMP_ON)
    {
        return;
    }

    s_pumpState = PUMP_ON;
    printf("[ACTUATOR] BOM BAT\n");
}

void HAL_TurnPumpOff(void)
{
    if (s_pumpState == PUMP_OFF)
    {
        return;
    }

    s_pumpState = PUMP_OFF;
    printf("[ACTUATOR] BOM TAT\n");
}

void HAL_SetLedState(LedState_t state)
{
    if (s_ledState == state)
    {
        return;
    }

    s_ledState = state;
    const char *label = "OFF";
    switch (state)
    {
        case LED_GREEN:
            label = "XANH (BINH THUONG)";
            break;
        case LED_YELLOW:
            label = "VANG (DANG TUOI)";
            break;
        case LED_RED:
            label = "DO (CANH BAO)";
            break;
        case LED_OFF:
        default:
            label = "TAT";
            break;
    }

    printf("[ACTUATOR] LED -> %s\n", label);
}
