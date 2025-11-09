/**
 * \file            book.c
 * \brief           Triển khai các hàm quản lý sách
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

#include "book.h"
#include <stdio.h>
#include <string.h>

/**
 * \brief           Khởi tạo danh sách sách
 * \param[in,out]   list: Con trỏ tới danh sách sách
 */
void
book_init(book_list_t* list) {
    if (list != NULL) {
        list->count = 0;
        memset(list->books, 0, sizeof(list->books));
    }
}

/**
 * \brief           Thêm sách mới vào danh sách
 * \param[in,out]   list: Con trỏ tới danh sách sách
 * \param[in]       book_id: ID của sách
 * \param[in]       title: Tiêu đề sách
 * \param[in]       author: Tác giả
 * \return          \ref BOOK_OK nếu thành công, \ref book_status_t nếu lỗi
 */
book_status_t
book_add(book_list_t* list, uint32_t book_id, const char* title, const char* author) {
    if (list == NULL || title == NULL || author == NULL) {
        return BOOK_INVALID_INPUT;
    }

    /* Kiểm tra ID hợp lệ */
    if (!is_valid_id(book_id)) {
        return BOOK_INVALID_INPUT;
    }

    /* Kiểm tra chuỗi rỗng */
    if (is_string_empty(title) || is_string_empty(author)) {
        return BOOK_INVALID_INPUT;
    }

    /* Kiểm tra danh sách đã đầy */
    if (list->count >= MAX_BOOKS) {
        return BOOK_FULL;
    }

    /* Kiểm tra ID đã tồn tại */
    if (book_find_by_id(list, book_id) != NULL) {
        return BOOK_ALREADY_EXISTS;
    }

    /* Thêm sách mới */
    book_t* new_book = &list->books[list->count];
    new_book->book_id = book_id;
    strncpy(new_book->title, title, MAX_TITLE_LENGTH - 1);
    new_book->title[MAX_TITLE_LENGTH - 1] = '\0';
    strncpy(new_book->author, author, MAX_AUTHOR_LENGTH - 1);
    new_book->author[MAX_AUTHOR_LENGTH - 1] = '\0';
    new_book->is_borrowed = 0;

    list->count++;
    return BOOK_OK;
}

/**
 * \brief           Cập nhật thông tin sách
 * \param[in,out]   list: Con trỏ tới danh sách sách
 * \param[in]       book_id: ID của sách cần cập nhật
 * \param[in]       title: Tiêu đề mới
 * \param[in]       author: Tác giả mới
 * \return          \ref BOOK_OK nếu thành công, \ref book_status_t nếu lỗi
 */
book_status_t
book_update(book_list_t* list, uint32_t book_id, const char* title, const char* author) {
    book_t* book;

    if (list == NULL || title == NULL || author == NULL) {
        return BOOK_INVALID_INPUT;
    }

    /* Kiểm tra chuỗi rỗng */
    if (is_string_empty(title) || is_string_empty(author)) {
        return BOOK_INVALID_INPUT;
    }

    /* Tìm sách */
    book = book_find_by_id(list, book_id);
    if (book == NULL) {
        return BOOK_NOT_FOUND;
    }

    /* Cập nhật thông tin */
    strncpy(book->title, title, MAX_TITLE_LENGTH - 1);
    book->title[MAX_TITLE_LENGTH - 1] = '\0';
    strncpy(book->author, author, MAX_AUTHOR_LENGTH - 1);
    book->author[MAX_AUTHOR_LENGTH - 1] = '\0';

    return BOOK_OK;
}

/**
 * \brief           Xóa sách khỏi danh sách
 * \param[in,out]   list: Con trỏ tới danh sách sách
 * \param[in]       book_id: ID của sách cần xóa
 * \return          \ref BOOK_OK nếu thành công, \ref book_status_t nếu lỗi
 */
book_status_t
book_delete(book_list_t* list, uint32_t book_id) {
    size_t i;

    if (list == NULL) {
        return BOOK_INVALID_INPUT;
    }

    /* Tìm vị trí sách */
    for (i = 0; i < list->count; i++) {
        if (list->books[i].book_id == book_id) {
            /* Kiểm tra sách có đang được mượn */
            if (list->books[i].is_borrowed) {
                return BOOK_IS_BORROWED;
            }

            /* Dịch chuyển các phần tử phía sau lên */
            if (i < list->count - 1) {
                memmove(&list->books[i], &list->books[i + 1],
                        (list->count - i - 1) * sizeof(book_t));
            }

            list->count--;
            return BOOK_OK;
        }
    }

    return BOOK_NOT_FOUND;
}

/**
 * \brief           Tìm sách theo ID
 * \param[in]       list: Con trỏ tới danh sách sách
 * \param[in]       book_id: ID của sách cần tìm
 * \return          Con trỏ tới sách nếu tìm thấy, NULL nếu không tìm thấy
 */
book_t*
book_find_by_id(book_list_t* list, uint32_t book_id) {
    size_t i;

    if (list == NULL) {
        return NULL;
    }

    for (i = 0; i < list->count; i++) {
        if (list->books[i].book_id == book_id) {
            return &list->books[i];
        }
    }

    return NULL;
}

/**
 * \brief           Đặt trạng thái mượn cho sách
 * \param[in,out]   list: Con trỏ tới danh sách sách
 * \param[in]       book_id: ID của sách
 * \param[in]       is_borrowed: Trạng thái mượn (1 = đã mượn, 0 = có sẵn)
 * \return          \ref BOOK_OK nếu thành công, \ref book_status_t nếu lỗi
 */
book_status_t
book_set_borrowed(book_list_t* list, uint32_t book_id, uint8_t is_borrowed) {
    book_t* book;

    if (list == NULL) {
        return BOOK_INVALID_INPUT;
    }

    book = book_find_by_id(list, book_id);
    if (book == NULL) {
        return BOOK_NOT_FOUND;
    }

    /* Kiểm tra trạng thái hiện tại */
    if (is_borrowed && book->is_borrowed) {
        return BOOK_IS_BORROWED;
    }

    if (!is_borrowed && !book->is_borrowed) {
        return BOOK_NOT_BORROWED;
    }

    book->is_borrowed = is_borrowed;
    return BOOK_OK;
}

/**
 * \brief           Hiển thị thông tin một cuốn sách
 * \param[in]       book: Con trỏ tới sách cần hiển thị
 */
void
book_display_one(const book_t* book) {
    if (book == NULL) {
        return;
    }

    printf("  %-10u | %-40s | %-30s | %-15s\n",
           book->book_id,
           book->title,
           book->author,
           book->is_borrowed ? "Đang được mượn" : "Có sẵn");
}

/**
 * \brief           Hiển thị tất cả sách trong danh sách
 * \param[in]       list: Con trỏ tới danh sách sách
 */
void
book_display_all(const book_list_t* list) {
    size_t i;

    if (list == NULL || list->count == 0) {
        printf("\n  Danh sách sách trống!\n");
        return;
    }

    printf("\n  %-10s | %-40s | %-30s | %-15s\n", "ID", "Tiêu đề", "Tác giả", "Trạng thái");
    print_separator();

    for (i = 0; i < list->count; i++) {
        book_display_one(&list->books[i]);
    }

    printf("\n  Tổng số sách: %zu\n", list->count);
}

/**
 * \brief           Hiển thị các sách có sẵn (chưa được mượn)
 * \param[in]       list: Con trỏ tới danh sách sách
 */
void
book_display_available(const book_list_t* list) {
    size_t i;
    size_t count;

    if (list == NULL) {
        return;
    }

    count = 0;
    printf("\n  %-10s | %-40s | %-30s | %-15s\n", "ID", "Tiêu đề", "Tác giả", "Trạng thái");
    print_separator();

    for (i = 0; i < list->count; i++) {
        if (!list->books[i].is_borrowed) {
            book_display_one(&list->books[i]);
            count++;
        }
    }

    if (count == 0) {
        printf("\n  Không có sách nào có sẵn!\n");
    } else {
        printf("\n  Tổng số sách có sẵn: %zu\n", count);
    }
}

/**
 * \brief           Tìm kiếm sách theo tiêu đề
 * \param[in]       list: Con trỏ tới danh sách sách
 * \param[in]       title: Tiêu đề cần tìm (hỗ trợ tìm kiếm một phần)
 */
void
book_search_by_title(const book_list_t* list, const char* title) {
    size_t i;
    size_t count;

    if (list == NULL || title == NULL) {
        return;
    }

    count = 0;
    printf("\n  %-10s | %-40s | %-30s | %-15s\n", "ID", "Tiêu đề", "Tác giả", "Trạng thái");
    print_separator();

    for (i = 0; i < list->count; i++) {
        if (string_contains(list->books[i].title, title)) {
            book_display_one(&list->books[i]);
            count++;
        }
    }

    if (count == 0) {
        printf("\n  Không tìm thấy sách nào với tiêu đề: %s\n", title);
    } else {
        printf("\n  Tìm thấy %zu sách\n", count);
    }
}

/**
 * \brief           Tìm kiếm sách theo tác giả
 * \param[in]       list: Con trỏ tới danh sách sách
 * \param[in]       author: Tên tác giả cần tìm (hỗ trợ tìm kiếm một phần)
 */
void
book_search_by_author(const book_list_t* list, const char* author) {
    size_t i;
    size_t count;

    if (list == NULL || author == NULL) {
        return;
    }

    count = 0;
    printf("\n  %-10s | %-40s | %-30s | %-15s\n", "ID", "Tiêu đề", "Tác giả", "Trạng thái");
    print_separator();

    for (i = 0; i < list->count; i++) {
        if (string_contains(list->books[i].author, author)) {
            book_display_one(&list->books[i]);
            count++;
        }
    }

    if (count == 0) {
        printf("\n  Không tìm thấy sách nào của tác giả: %s\n", author);
    } else {
        printf("\n  Tìm thấy %zu sách\n", count);
    }
}

/**
 * \brief           Đếm tổng số sách
 * \param[in]       list: Con trỏ tới danh sách sách
 * \return          Tổng số sách
 */
size_t
book_count_total(const book_list_t* list) {
    if (list == NULL) {
        return 0;
    }
    return list->count;
}

/**
 * \brief           Đếm số sách đang được mượn
 * \param[in]       list: Con trỏ tới danh sách sách
 * \return          Số sách đang được mượn
 */
size_t
book_count_borrowed(const book_list_t* list) {
    size_t i;
    size_t count;

    if (list == NULL) {
        return 0;
    }

    count = 0;
    for (i = 0; i < list->count; i++) {
        if (list->books[i].is_borrowed) {
            count++;
        }
    }

    return count;
}

/**
 * \brief           Đếm số sách có sẵn
 * \param[in]       list: Con trỏ tới danh sách sách
 * \return          Số sách có sẵn
 */
size_t
book_count_available(const book_list_t* list) {
    size_t i;
    size_t count;

    if (list == NULL) {
        return 0;
    }

    count = 0;
    for (i = 0; i < list->count; i++) {
        if (!list->books[i].is_borrowed) {
            count++;
        }
    }

    return count;
}

