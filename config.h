#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <stdint.h>

/*
 * Cấu hình lõi: enum, struct và hằng số dùng chung toàn hệ thống.
 * Các giá trị mặc định ở cuối file giúp việc khởi tạo đồng nhất giữa main và controller.
 */

/* Chế độ hoạt động hệ thống */
typedef enum
{
    MODE_AUTO = 0,
    MODE_MANUAL
} SystemMode_t;

typedef enum
{
    PUMP_OFF = 0,
    PUMP_ON
} PumpState_t;

typedef enum
{
    LED_OFF = 0,
    LED_GREEN,
    LED_YELLOW,
    LED_RED
} LedState_t;

/* Cấu trúc dữ liệu chính */
typedef struct
{
    float soilMoisturePercent;
    float ambientTemperatureC;
    uint32_t lastReadTime_s;
} SensorData_t;

typedef struct
{
    float minMoistureThreshold;
    float maxMoistureThreshold;
    uint32_t sensorReadInterval_s;
    uint32_t maxWateringDuration_s;
    uint32_t manualWateringDuration_s;
} SystemSettings_t;

typedef struct
{
    SystemMode_t mode;
    PumpState_t pumpState;
    LedState_t ledState;
    bool autoWateringActive;
    bool manualWateringActive;
    uint32_t pumpStartedAt_s;
    uint32_t manualWaterStartedAt_s;
} SystemState_t;

/* Giá trị mặc định */
#define DEFAULT_MIN_MOISTURE             35.0f
#define DEFAULT_MAX_MOISTURE             65.0f
#define DEFAULT_SENSOR_INTERVAL_SEC      5U
#define DEFAULT_MAX_WATER_DURATION_SEC   20U
#define DEFAULT_MANUAL_DURATION_SEC      10U

#endif
