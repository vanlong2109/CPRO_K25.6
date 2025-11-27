/*
 * HAL - Nút nhấn giả lập.
 * Mục tiêu: giữ giao diện giống phần cứng (polling, trả về bool), phần triển khai có thể thay thế.
 * Phiên bản mô phỏng: trả về true tại các mốc thời gian cố định, tránh cần input người dùng.
 */
#ifndef HAL_BUTTONS_H
#define HAL_BUTTONS_H

#include <stdbool.h>
#include <stdint.h>
#include "../config.h"

/* Khởi tạo state mô phỏng nút, reset anti-dup chống lặp lại cùng timestamp */
void HAL_Buttons_Init(void);

/* Kiểm tra nút chuyển chế độ (AUTO <-> MANUAL), true nếu vừa được nhấn tại thời điểm now_s */
bool HAL_Button_ModeTogglePressed(uint32_t now_s);

/* Kiểm tra nút tưới thủ công, true nếu vừa được nhấn tại thời điểm now_s */
bool HAL_Button_ManualWaterPressed(uint32_t now_s);

#endif
