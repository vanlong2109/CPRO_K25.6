/*
 * Mô phỏng cảm biến:
 *  - Độ ẩm đất thay đổi theo một chuỗi giả lập.
 *  - Nhiệt độ dao động nhẹ quanh 27-28 độ C.
 */
#include <stddef.h>
#include <time.h>
#include "hal_sensors.h"

static time_t s_startTime = 0;

void HAL_Sensors_Init(void)
{
    s_startTime = time(NULL);
}

float HAL_ReadSoilMoisture(void)
{
    static const float samples[] = {42.0f, 40.0f, 38.5f, 36.0f, 33.0f, 30.0f, 27.5f, 25.0f, 23.0f, 35.0f, 48.0f, 58.0f, 66.0f, 71.0f};
    static size_t index = 0;

    float value = samples[index];
    index = (index + 1) % (sizeof(samples) / sizeof(samples[0]));
    return value;
}

float HAL_ReadAmbientTemperature(void)
{
    static const float temps[] = {27.0f, 27.3f, 27.5f, 27.8f, 28.0f};
    static size_t index = 0;

    float value = temps[index];
    index = (index + 1) % (sizeof(temps) / sizeof(temps[0]));
    return value;
}

uint32_t HAL_GetSystemTimeSeconds(void)
{
    time_t now = time(NULL);
    if (s_startTime == 0)
    {
        s_startTime = now;
    }
    return (uint32_t)(now - s_startTime);
}
