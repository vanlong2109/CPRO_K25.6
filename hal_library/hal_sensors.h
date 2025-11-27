/*
 * HAL - Cảm biến giả lập.
 * API giữ giống đọc ADC thực tế: trả về float, không cần tham số.
 * Phiên bản mô phỏng tuần tự duyệt qua mảng giá trị mẫu để kiểm thử logic điều khiển.
 */
#ifndef HAL_SENSORS_H
#define HAL_SENSORS_H

#include <stdint.h>
#include "../config.h"

/* Khởi tạo thời điểm bắt đầu (làm mốc cho đồng hồ ảo) */
void HAL_Sensors_Init(void);

/* Đọc độ ẩm đất (0-100%), mô phỏng từ chuỗi mẫu */
float HAL_ReadSoilMoisture(void);

/* Đọc nhiệt độ môi trường, dao động nhẹ quanh 27-28C */
float HAL_ReadAmbientTemperature(void);

/* Đồng hồ ảo, trả về số giây kể từ khi Init */
uint32_t HAL_GetSystemTimeSeconds(void);

#endif
