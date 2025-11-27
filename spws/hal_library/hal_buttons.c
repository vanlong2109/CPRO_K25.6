/*
 * Mô phỏng nút nhấn:
 *  - Nút 1: chuyển chế độ AUTO/MANUAL.
 *  - Nút 2: kích hoạt tưới thủ công trong MANUAL.
 * Lịch mô phỏng:
 *    - Nút 1 nhấn tại giây 15 và 40.
 *    - Nút 2 nhấn tại giây 18 và 22 (chỉ có tác dụng khi đang MANUAL).
 */
#include <stdio.h>
#include "hal_buttons.h"

static uint32_t s_lastModeToggleTime = 0;
static uint32_t s_lastManualPressTime = 0;

void HAL_Buttons_Init(void)
{
    s_lastModeToggleTime = 0;
    s_lastManualPressTime = 0;
}

static bool is_time_in_list(uint32_t now_s, const uint32_t *timeList, uint32_t len, uint32_t *lastTime)
{
    for (uint32_t i = 0; i < len; ++i)
    {
        if (now_s == timeList[i] && *lastTime != now_s)
        {
            *lastTime = now_s;
            return true;
        }
    }
    return false;
}

bool HAL_Button_ModeTogglePressed(uint32_t now_s)
{
    const uint32_t schedule[] = {15U, 40U};
    bool pressed = is_time_in_list(now_s, schedule, sizeof(schedule) / sizeof(schedule[0]), &s_lastModeToggleTime);
    if (pressed)
    {
        printf("[BUTTON] NUT CHUYEN CHE DO DUOC NHAN (t=%us)\n", now_s);
    }
    return pressed;
}

bool HAL_Button_ManualWaterPressed(uint32_t now_s)
{
    const uint32_t schedule[] = {18U, 22U};
    bool pressed = is_time_in_list(now_s, schedule, sizeof(schedule) / sizeof(schedule[0]), &s_lastManualPressTime);
    if (pressed)
    {
        printf("[BUTTON] NUT TUOI THU CONG DUOC NHAN (t=%us)\n", now_s);
    }
    return pressed;
}
