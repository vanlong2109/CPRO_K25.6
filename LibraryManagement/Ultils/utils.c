/**
 * \file            utils.c
 * \brief           Triển khai các hàm tiện ích cho ứng dụng quản lý thư viện
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

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * \brief           Xóa màn hình console
 */
void
clear_screen(void) {
    int32_t result;
#ifdef _WIN32
    result = system("cls");
#else
    result = system("clear");
#endif
    (void)result; /* Bỏ qua cảnh báo unused result */
}

/**
 * \brief           Tạm dừng màn hình và chờ người dùng nhấn phím
 */
void
pause_screen(void) {
    printf("\nNhấn Enter để tiếp tục...");
    clear_input_buffer();
    getchar();
}

/**
 * \brief           Xóa bộ đệm đầu vào
 */
void
clear_input_buffer(void) {
    int32_t c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/**
 * \brief           In dòng phân cách
 */
void
print_separator(void) {
    printf("================================================================================\n");
}

/**
 * \brief           In tiêu đề với định dạng đẹp
 * \param[in]       title: Chuỗi tiêu đề cần in
 */
void
print_header(const char* title) {
    print_separator();
    printf("  %s\n", title);
    print_separator();
}

/**
 * \brief           Đọc chuỗi từ bàn phím với validation
 * \param[out]      buffer: Bộ đệm lưu chuỗi đọc được
 * \param[in]       max_len: Độ dài tối đa của chuỗi
 * \param[in]       prompt: Thông báo nhắc nhở người dùng
 * \return          \ref UTILS_OK nếu thành công, \ref utils_status_t nếu lỗi
 */
utils_status_t
read_string(char* buffer, size_t max_len, const char* prompt) {
    if (buffer == NULL || max_len == 0) {
        return UTILS_INVALID_INPUT;
    }

    printf("%s", prompt);
    
    if (fgets(buffer, max_len, stdin) == NULL) {
        return UTILS_ERROR;
    }

    /* Xóa ký tự newline nếu có */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        /* Nếu không có newline, xóa bộ đệm */
        clear_input_buffer();
    }

    /* Loại bỏ khoảng trắng đầu cuối */
    trim_string(buffer);

    /* Kiểm tra chuỗi rỗng */
    if (is_string_empty(buffer)) {
        return UTILS_EMPTY_STRING;
    }

    return UTILS_OK;
}

/**
 * \brief           Đọc số nguyên có dấu từ bàn phím
 * \param[out]      value: Con trỏ lưu giá trị đọc được
 * \param[in]       prompt: Thông báo nhắc nhở người dùng
 * \return          \ref UTILS_OK nếu thành công, \ref utils_status_t nếu lỗi
 */
utils_status_t
read_int(int32_t* value, const char* prompt) {
    char buffer[MAX_INPUT_LENGTH];
    char* endptr;

    if (value == NULL) {
        return UTILS_INVALID_INPUT;
    }

    printf("%s", prompt);
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return UTILS_ERROR;
    }

    /* Chuyển đổi chuỗi sang số */
    *value = strtol(buffer, &endptr, 10);

    /* Kiểm tra lỗi chuyển đổi */
    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return UTILS_INVALID_INPUT;
    }

    return UTILS_OK;
}

/**
 * \brief           Đọc số nguyên không dấu từ bàn phím
 * \param[out]      value: Con trỏ lưu giá trị đọc được
 * \param[in]       prompt: Thông báo nhắc nhở người dùng
 * \return          \ref UTILS_OK nếu thành công, \ref utils_status_t nếu lỗi
 */
utils_status_t
read_uint(uint32_t* value, const char* prompt) {
    char buffer[MAX_INPUT_LENGTH];
    char* endptr;
    long temp;

    if (value == NULL) {
        return UTILS_INVALID_INPUT;
    }

    printf("%s", prompt);
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return UTILS_ERROR;
    }

    /* Chuyển đổi chuỗi sang số */
    temp = strtol(buffer, &endptr, 10);

    /* Kiểm tra lỗi chuyển đổi */
    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return UTILS_INVALID_INPUT;
    }

    /* Kiểm tra số âm */
    if (temp < 0) {
        return UTILS_INVALID_INPUT;
    }

    *value = (uint32_t)temp;
    return UTILS_OK;
}

/**
 * \brief           Kiểm tra chuỗi có rỗng hay không
 * \param[in]       str: Chuỗi cần kiểm tra
 * \return          1 nếu chuỗi rỗng, 0 nếu không rỗng
 */
uint8_t
is_string_empty(const char* str) {
    if (str == NULL) {
        return 1;
    }

    while (*str != '\0') {
        if (!isspace((unsigned char)*str)) {
            return 0;
        }
        str++;
    }

    return 1;
}

/**
 * \brief           Kiểm tra ID có hợp lệ hay không
 * \param[in]       id: ID cần kiểm tra
 * \return          1 nếu hợp lệ, 0 nếu không hợp lệ
 */
uint8_t
is_valid_id(uint32_t id) {
    return (id >= MIN_ID_VALUE && id <= MAX_ID_VALUE);
}

/**
 * \brief           Loại bỏ khoảng trắng đầu và cuối chuỗi
 * \param[in,out]   str: Chuỗi cần xử lý
 */
void
trim_string(char* str) {
    char* start;
    char* end;

    if (str == NULL || *str == '\0') {
        return;
    }

    /* Tìm ký tự đầu tiên không phải khoảng trắng */
    start = str;
    while (isspace((unsigned char)*start)) {
        start++;
    }

    /* Nếu toàn bộ chuỗi là khoảng trắng */
    if (*start == '\0') {
        *str = '\0';
        return;
    }

    /* Tìm ký tự cuối cùng không phải khoảng trắng */
    end = str + strlen(str) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }

    /* Ghi đè chuỗi đã trim */
    size_t len = (end - start) + 1;
    if (start != str) {
        memmove(str, start, len);
    }
    str[len] = '\0';
}

/**
 * \brief           Chuyển chuỗi sang chữ thường
 * \param[in,out]   str: Chuỗi cần chuyển đổi
 */
void
to_lowercase(char* str) {
    if (str == NULL) {
        return;
    }

    while (*str != '\0') {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

/**
 * \brief           Kiểm tra chuỗi con có tồn tại trong chuỗi cha (không phân biệt hoa thường)
 * \param[in]       haystack: Chuỗi cha
 * \param[in]       needle: Chuỗi con cần tìm
 * \return          1 nếu tìm thấy, 0 nếu không tìm thấy
 */
int32_t
string_contains(const char* haystack, const char* needle) {
    char haystack_lower[MAX_STRING_LENGTH];
    char needle_lower[MAX_STRING_LENGTH];

    if (haystack == NULL || needle == NULL) {
        return 0;
    }

    /* Sao chép và chuyển sang chữ thường */
    strncpy(haystack_lower, haystack, MAX_STRING_LENGTH - 1);
    haystack_lower[MAX_STRING_LENGTH - 1] = '\0';
    to_lowercase(haystack_lower);

    strncpy(needle_lower, needle, MAX_STRING_LENGTH - 1);
    needle_lower[MAX_STRING_LENGTH - 1] = '\0';
    to_lowercase(needle_lower);

    /* Tìm kiếm chuỗi con */
    return (strstr(haystack_lower, needle_lower) != NULL) ? 1 : 0;
}

