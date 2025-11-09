/**
 * \file            utils.h
 * \brief           Các hàm tiện ích cho ứng dụng quản lý thư viện
 */

/*
 * Copyright (c) 2025 Phạm Văn Long
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of Library Management System.
 *
 * Author:          Phạm Văn Long
 */

#ifndef UTILS_HDR_H
#define UTILS_HDR_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Định nghĩa các hằng số */
#define MAX_STRING_LENGTH           256
#define MAX_INPUT_LENGTH            512
#define MIN_ID_VALUE                1
#define MAX_ID_VALUE                999999

/**
 * \brief           Trạng thái trả về của các hàm
 */
typedef enum {
    UTILS_OK = 0,                               /*!< Thành công */
    UTILS_ERROR,                                /*!< Lỗi chung */
    UTILS_INVALID_INPUT,                        /*!< Dữ liệu đầu vào không hợp lệ */
    UTILS_EMPTY_STRING,                         /*!< Chuỗi rỗng */
    UTILS_OUT_OF_RANGE,                         /*!< Giá trị nằm ngoài phạm vi cho phép */
} utils_status_t;

/* Khai báo các hàm tiện ích */
void            clear_screen(void);
void            pause_screen(void);
void            clear_input_buffer(void);
void            print_separator(void);
void            print_header(const char* title);

utils_status_t  read_string(char* buffer, size_t max_len, const char* prompt);
utils_status_t  read_int(int32_t* value, const char* prompt);
utils_status_t  read_uint(uint32_t* value, const char* prompt);

uint8_t         is_string_empty(const char* str);
uint8_t         is_valid_id(uint32_t id);
void            trim_string(char* str);
void            to_lowercase(char* str);
int32_t         string_contains(const char* haystack, const char* needle);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* UTILS_HDR_H */

