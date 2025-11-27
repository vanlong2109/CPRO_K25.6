/*
 * Bộ điều khiển chính cho Smart Plant Watering System.
 * Chứa các hàm thuần logic (không đụng tới phần cứng trực tiếp), giúp dễ unit test.
 */
#ifndef SPWS_CONTROLLER_H
#define SPWS_CONTROLLER_H

#include <stdbool.h>
#include "../config.h"

/* Khởi tạo state/settings/sensorData về giá trị mặc định */
void SPWS_InitDefaults(SystemState_t *state, SystemSettings_t *settings, SensorData_t *sensorData);

/* Logic AUTO: bật/tắt bơm dựa trên ngưỡng độ ẩm và thời gian tối đa */
void SPWS_RunAutoMode(SystemState_t *state, const SystemSettings_t *settings, const SensorData_t *sensorData, uint32_t now_s);

/* Logic MANUAL: xử lý nhấn nút tưới tay và auto-stop sau manualWateringDuration_s */
void SPWS_RunManualMode(SystemState_t *state, const SystemSettings_t *settings, uint32_t now_s, bool manualPressed);

/* Dừng bơm an toàn, reset cờ chu kỳ, in lý do nếu có */
void SPWS_StopPump(SystemState_t *state, const char *reason);

/* Cập nhật LED/bơm theo state hiện tại */
void SPWS_ApplyOutputs(SystemState_t *state);

#endif
