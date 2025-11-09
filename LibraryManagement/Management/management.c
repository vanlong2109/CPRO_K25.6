/**
 * \file            management.c
 * \brief           Triển khai các hàm quản lý mượn/trả sách và thống kê
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

#include "management.h"
#include "../Ultils/utils.h"
#include <stdio.h>

/**
 * \brief           Cho phép người dùng mượn sách
 * \param[in,out]   library: Con trỏ tới cấu trúc thư viện
 * \param[in]       user_id: ID của người dùng
 * \param[in]       book_id: ID của sách cần mượn
 * \return          \ref MGMT_OK nếu thành công, \ref mgmt_status_t nếu lỗi
 */
mgmt_status_t
mgmt_borrow_book(library_t* library, uint32_t user_id, uint32_t book_id) {
    user_t* user;
    book_t* book;
    user_status_t user_status;
    book_status_t book_status;

    if (library == NULL || library->books == NULL || library->users == NULL) {
        return MGMT_INVALID_INPUT;
    }

    /* Tìm người dùng */
    user = user_find_by_id(library->users, user_id);
    if (user == NULL) {
        return MGMT_USER_NOT_FOUND;
    }

    /* Tìm sách */
    book = book_find_by_id(library->books, book_id);
    if (book == NULL) {
        return MGMT_BOOK_NOT_FOUND;
    }

    /* Kiểm tra sách đã được mượn chưa */
    if (book->is_borrowed) {
        return MGMT_BOOK_ALREADY_BORROWED;
    }

    /* Kiểm tra người dùng đã đạt giới hạn mượn sách chưa */
    if (user->borrowed_count >= MAX_BORROWED_BOOKS) {
        return MGMT_USER_LIMIT_REACHED;
    }

    /* Thêm sách vào danh sách mượn của người dùng */
    user_status = user_add_borrowed_book(user, book_id);
    if (user_status != USER_OK) {
        return MGMT_ERROR;
    }

    /* Đánh dấu sách đã được mượn */
    book_status = book_set_borrowed(library->books, book_id, 1);
    if (book_status != BOOK_OK) {
        /* Rollback: xóa sách khỏi danh sách mượn của người dùng */
        user_remove_borrowed_book(user, book_id);
        return MGMT_ERROR;
    }

    return MGMT_OK;
}

/**
 * \brief           Cho phép người dùng trả sách
 * \param[in,out]   library: Con trỏ tới cấu trúc thư viện
 * \param[in]       user_id: ID của người dùng
 * \param[in]       book_id: ID của sách cần trả
 * \return          \ref MGMT_OK nếu thành công, \ref mgmt_status_t nếu lỗi
 */
mgmt_status_t
mgmt_return_book(library_t* library, uint32_t user_id, uint32_t book_id) {
    user_t* user;
    book_t* book;
    user_status_t user_status;
    book_status_t book_status;

    if (library == NULL || library->books == NULL || library->users == NULL) {
        return MGMT_INVALID_INPUT;
    }

    /* Tìm người dùng */
    user = user_find_by_id(library->users, user_id);
    if (user == NULL) {
        return MGMT_USER_NOT_FOUND;
    }

    /* Tìm sách */
    book = book_find_by_id(library->books, book_id);
    if (book == NULL) {
        return MGMT_BOOK_NOT_FOUND;
    }

    /* Kiểm tra sách có đang được mượn không */
    if (!book->is_borrowed) {
        return MGMT_BOOK_NOT_BORROWED;
    }

    /* Kiểm tra người dùng có đang mượn sách này không */
    if (!user_has_borrowed_book(user, book_id)) {
        return MGMT_BOOK_NOT_BORROWED;
    }

    /* Xóa sách khỏi danh sách mượn của người dùng */
    user_status = user_remove_borrowed_book(user, book_id);
    if (user_status != USER_OK) {
        return MGMT_ERROR;
    }

    /* Đánh dấu sách đã được trả */
    book_status = book_set_borrowed(library->books, book_id, 0);
    if (book_status != BOOK_OK) {
        /* Rollback: thêm lại sách vào danh sách mượn của người dùng */
        user_add_borrowed_book(user, book_id);
        return MGMT_ERROR;
    }

    return MGMT_OK;
}

/**
 * \brief           Hiển thị thống kê tổng quan của thư viện
 * \param[in]       library: Con trỏ tới cấu trúc thư viện
 */
void
mgmt_display_statistics(const library_t* library) {
    size_t total_books;
    size_t borrowed_books;
    size_t available_books;
    size_t total_users;

    if (library == NULL || library->books == NULL || library->users == NULL) {
        printf("\n  Lỗi: Dữ liệu thư viện không hợp lệ!\n");
        return;
    }

    total_books = book_count_total(library->books);
    borrowed_books = book_count_borrowed(library->books);
    available_books = book_count_available(library->books);
    total_users = user_count_total(library->users);

    print_header("THỐNG KÊ TỔNG QUAN THƯ VIỆN");
    printf("\n");
    printf("  Tổng số sách:              %zu\n", total_books);
    printf("  Số sách đang được mượn:    %zu\n", borrowed_books);
    printf("  Số sách có sẵn:            %zu\n", available_books);
    printf("  Tổng số người dùng:        %zu\n", total_users);
    printf("\n");
}

/**
 * \brief           Hiển thị thông tin người dùng kèm danh sách sách đang mượn
 * \param[in]       library: Con trỏ tới cấu trúc thư viện
 * \param[in]       user_id: ID của người dùng
 */
void
mgmt_display_user_books(const library_t* library, uint32_t user_id) {
    user_t* user;
    book_t* book;
    size_t i;

    if (library == NULL || library->books == NULL || library->users == NULL) {
        printf("\n  Lỗi: Dữ liệu thư viện không hợp lệ!\n");
        return;
    }

    /* Tìm người dùng */
    user = user_find_by_id(library->users, user_id);
    if (user == NULL) {
        printf("\n  Lỗi: Không tìm thấy người dùng với ID %u!\n", user_id);
        return;
    }

    print_header("THÔNG TIN NGƯỜI DÙNG");
    printf("\n  ID người dùng: %u\n", user->user_id);
    printf("  Tên: %s\n", user->name);
    printf("  Số sách đang mượn: %zu/%d\n", user->borrowed_count, MAX_BORROWED_BOOKS);

    if (user->borrowed_count > 0) {
        printf("\n  Danh sách sách đang mượn:\n");
        print_separator();
        printf("  %-10s | %-40s | %-30s\n", "ID", "Tiêu đề", "Tác giả");
        print_separator();

        for (i = 0; i < user->borrowed_count; i++) {
            book = book_find_by_id(library->books, user->borrowed_books[i]);
            if (book != NULL) {
                printf("  %-10u | %-40s | %-30s\n",
                       book->book_id,
                       book->title,
                       book->author);
            }
        }
    } else {
        printf("\n  Chưa mượn sách nào.\n");
    }
    printf("\n");
}

