/**
 * \file            user.h
 * \brief           Module quản lý người dùng trong thư viện
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

#ifndef USER_HDR_H
#define USER_HDR_H

#include <stdint.h>
#include <stddef.h>
#include "../Ultils/utils.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Định nghĩa các hằng số */
#define MAX_NAME_LENGTH             256
#define MAX_USERS                   500
#define MAX_BORROWED_BOOKS          5

/**
 * \brief           Trạng thái trả về của các hàm quản lý người dùng
 */
typedef enum {
    USER_OK = 0,                                /*!< Thành công */
    USER_ERROR,                                 /*!< Lỗi chung */
    USER_INVALID_INPUT,                         /*!< Dữ liệu đầu vào không hợp lệ */
    USER_NOT_FOUND,                             /*!< Không tìm thấy người dùng */
    USER_ALREADY_EXISTS,                        /*!< Người dùng đã tồn tại */
    USER_FULL,                                  /*!< Danh sách người dùng đã đầy */
    USER_HAS_BORROWED_BOOKS,                    /*!< Người dùng đang mượn sách */
    USER_BORROW_LIMIT_REACHED,                  /*!< Đã đạt giới hạn số sách mượn */
    USER_BOOK_NOT_BORROWED,                     /*!< Sách không có trong danh sách mượn */
} user_status_t;

/**
 * \brief           Cấu trúc dữ liệu của một người dùng
 */
typedef struct {
    uint32_t user_id;                           /*!< ID duy nhất của người dùng */
    char name[MAX_NAME_LENGTH];                 /*!< Tên người dùng */
    uint32_t borrowed_books[MAX_BORROWED_BOOKS];/*!< Danh sách ID sách đã mượn */
    size_t borrowed_count;                      /*!< Số lượng sách đang mượn */
} user_t;

/**
 * \brief           Cấu trúc quản lý danh sách người dùng
 */
typedef struct {
    user_t users[MAX_USERS];                    /*!< Mảng chứa các người dùng */
    size_t count;                               /*!< Số lượng người dùng hiện tại */
    uint32_t next_id;                           /*!< ID tiếp theo sẽ được gán */
} user_list_t;

/* Khai báo các hàm quản lý người dùng */
void            user_init(user_list_t* list);
user_status_t   user_add(user_list_t* list, const char* name, uint32_t* assigned_id);
user_status_t   user_add_with_id(user_list_t* list, uint32_t user_id, const char* name);
user_status_t   user_update(user_list_t* list, uint32_t user_id, const char* name);
user_status_t   user_delete(user_list_t* list, uint32_t user_id);
user_t*         user_find_by_id(user_list_t* list, uint32_t user_id);

user_status_t   user_add_borrowed_book(user_t* user, uint32_t book_id);
user_status_t   user_remove_borrowed_book(user_t* user, uint32_t book_id);
uint8_t         user_has_borrowed_book(const user_t* user, uint32_t book_id);

void            user_display_all(const user_list_t* list);
void            user_display_one(const user_t* user);
void            user_display_with_books(const user_t* user);

size_t          user_count_total(const user_list_t* list);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* USER_HDR_H */

