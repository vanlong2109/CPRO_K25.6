/**
 * \file            book.h
 * \brief           Module quản lý sách trong thư viện
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

#ifndef BOOK_HDR_H
#define BOOK_HDR_H

#include <stdint.h>
#include <stddef.h>
#include "../Ultils/utils.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Định nghĩa các hằng số */
#define MAX_TITLE_LENGTH            256
#define MAX_AUTHOR_LENGTH           256
#define MAX_BOOKS                   1000

/**
 * \brief           Trạng thái trả về của các hàm quản lý sách
 */
typedef enum {
    BOOK_OK = 0,                                /*!< Thành công */
    BOOK_ERROR,                                 /*!< Lỗi chung */
    BOOK_INVALID_INPUT,                         /*!< Dữ liệu đầu vào không hợp lệ */
    BOOK_NOT_FOUND,                             /*!< Không tìm thấy sách */
    BOOK_ALREADY_EXISTS,                        /*!< Sách đã tồn tại */
    BOOK_FULL,                                  /*!< Danh sách sách đã đầy */
    BOOK_IS_BORROWED,                           /*!< Sách đang được mượn */
    BOOK_NOT_BORROWED,                          /*!< Sách chưa được mượn */
} book_status_t;

/**
 * \brief           Cấu trúc dữ liệu của một cuốn sách
 */
typedef struct {
    uint32_t book_id;                           /*!< ID duy nhất của sách */
    char title[MAX_TITLE_LENGTH];               /*!< Tiêu đề sách */
    char author[MAX_AUTHOR_LENGTH];             /*!< Tác giả */
    uint8_t is_borrowed;                        /*!< Trạng thái mượn: 1 = đã mượn, 0 = có sẵn */
} book_t;

/**
 * \brief           Cấu trúc quản lý danh sách sách
 */
typedef struct {
    book_t books[MAX_BOOKS];                    /*!< Mảng chứa các sách */
    size_t count;                               /*!< Số lượng sách hiện tại */
    uint32_t next_id;                           /*!< ID tiếp theo sẽ được gán */
} book_list_t;

/* Khai báo các hàm quản lý sách */
void            book_init(book_list_t* list);
book_status_t   book_add(book_list_t* list, const char* title, const char* author, uint32_t* assigned_id);
book_status_t   book_add_with_id(book_list_t* list, uint32_t book_id, const char* title, const char* author);
book_status_t   book_update(book_list_t* list, uint32_t book_id, const char* title, const char* author);
book_status_t   book_delete(book_list_t* list, uint32_t book_id);
book_t*         book_find_by_id(book_list_t* list, uint32_t book_id);
book_status_t   book_set_borrowed(book_list_t* list, uint32_t book_id, uint8_t is_borrowed);

void            book_display_all(const book_list_t* list);
void            book_display_available(const book_list_t* list);
void            book_display_one(const book_t* book);
void            book_search_by_title(const book_list_t* list, const char* title);
void            book_search_by_author(const book_list_t* list, const char* author);

size_t          book_count_total(const book_list_t* list);
size_t          book_count_borrowed(const book_list_t* list);
size_t          book_count_available(const book_list_t* list);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BOOK_HDR_H */

