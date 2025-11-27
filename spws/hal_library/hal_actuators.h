/*
 * HAL - Bộ chấp hành: bơm và LED.
 * Chỉ mô phỏng in ra console, nhưng giữ API sạch để thay thế bằng GPIO/PWM thực tế.
 * - Init đặt trạng thái về OFF để tránh bật bơm ngoài ý muốn.
 * - TurnPumpOn/Off chịu trách nhiệm cập nhật trạng thái trong module và phát log.
 * - SetLedState chỉ nhận LedState_t và tự bỏ qua nếu không đổi, giảm nhấp nháy.
 */
#ifndef HAL_ACTUATORS_H
#define HAL_ACTUATORS_H

#include "../config.h"

/* Khởi tạo tài nguyên bơm/LED, gọi một lần ở System_Init */
void HAL_Actuators_Init(void);

/* Bật bơm, idempotent nếu đã bật */
void HAL_TurnPumpOn(void);

/* Tắt bơm, idempotent nếu đã tắt */
void HAL_TurnPumpOff(void);

/* Đặt trạng thái LED theo LedState_t (GREEN/YELLOW/RED/OFF) */
void HAL_SetLedState(LedState_t state);

#endif
