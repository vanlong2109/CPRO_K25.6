/**
 * \file            management.h
 * \brief           Module quản lý mượn/trả sách và các chức năng tổng hợp
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

#ifndef MANAGEMENT_HDR_H
#define MANAGEMENT_HDR_H

#include <stdint.h>
#include "../Book/book.h"
#include "../User/user.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           Trạng thái trả về của các hàm quản lý
 */
typedef enum {
    MGMT_OK = 0,                                /*!< Thành công */
    MGMT_ERROR,                                 /*!< Lỗi chung */
    MGMT_INVALID_INPUT,                         /*!< Dữ liệu đầu vào không hợp lệ */
    MGMT_BOOK_NOT_FOUND,                        /*!< Không tìm thấy sách */
    MGMT_USER_NOT_FOUND,                        /*!< Không tìm thấy người dùng */
    MGMT_BOOK_ALREADY_BORROWED,                 /*!< Sách đã được mượn */
    MGMT_BOOK_NOT_BORROWED,                     /*!< Sách chưa được mượn */
    MGMT_USER_LIMIT_REACHED,                    /*!< Người dùng đã mượn đủ số sách cho phép */
} mgmt_status_t;

/**
 * \brief           Cấu trúc quản lý toàn bộ hệ thống thư viện
 */
typedef struct {
    book_list_t* books;                         /*!< Con trỏ tới danh sách sách */
    user_list_t* users;                         /*!< Con trỏ tới danh sách người dùng */
} library_t;

/* Khai báo các hàm quản lý mượn/trả sách */
mgmt_status_t   mgmt_borrow_book(library_t* library, uint32_t user_id, uint32_t book_id);
mgmt_status_t   mgmt_return_book(library_t* library, uint32_t user_id, uint32_t book_id);

/* Khai báo các hàm hiển thị thống kê */
void            mgmt_display_statistics(const library_t* library);
void            mgmt_display_user_books(const library_t* library, uint32_t user_id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MANAGEMENT_HDR_H */

