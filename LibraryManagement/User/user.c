/**
 * \file            user.c
 * \brief           Triển khai các hàm quản lý người dùng
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

#include "user.h"
#include <stdio.h>
#include <string.h>

/**
 * \brief           Khởi tạo danh sách người dùng
 * \param[in,out]   list: Con trỏ tới danh sách người dùng
 */
void
user_init(user_list_t* list) {
    if (list != NULL) {
        list->count = 0;
        memset(list->users, 0, sizeof(list->users));
    }
}

/**
 * \brief           Thêm người dùng mới vào danh sách
 * \param[in,out]   list: Con trỏ tới danh sách người dùng
 * \param[in]       user_id: ID của người dùng
 * \param[in]       name: Tên người dùng
 * \return          \ref USER_OK nếu thành công, \ref user_status_t nếu lỗi
 */
user_status_t
user_add(user_list_t* list, uint32_t user_id, const char* name) {
    if (list == NULL || name == NULL) {
        return USER_INVALID_INPUT;
    }

    /* Kiểm tra ID hợp lệ */
    if (!is_valid_id(user_id)) {
        return USER_INVALID_INPUT;
    }

    /* Kiểm tra chuỗi rỗng */
    if (is_string_empty(name)) {
        return USER_INVALID_INPUT;
    }

    /* Kiểm tra danh sách đã đầy */
    if (list->count >= MAX_USERS) {
        return USER_FULL;
    }

    /* Kiểm tra ID đã tồn tại */
    if (user_find_by_id(list, user_id) != NULL) {
        return USER_ALREADY_EXISTS;
    }

    /* Thêm người dùng mới */
    user_t* new_user = &list->users[list->count];
    new_user->user_id = user_id;
    strncpy(new_user->name, name, MAX_NAME_LENGTH - 1);
    new_user->name[MAX_NAME_LENGTH - 1] = '\0';
    new_user->borrowed_count = 0;
    memset(new_user->borrowed_books, 0, sizeof(new_user->borrowed_books));

    list->count++;
    return USER_OK;
}

/**
 * \brief           Cập nhật thông tin người dùng
 * \param[in,out]   list: Con trỏ tới danh sách người dùng
 * \param[in]       user_id: ID của người dùng cần cập nhật
 * \param[in]       name: Tên mới
 * \return          \ref USER_OK nếu thành công, \ref user_status_t nếu lỗi
 */
user_status_t
user_update(user_list_t* list, uint32_t user_id, const char* name) {
    user_t* user;

    if (list == NULL || name == NULL) {
        return USER_INVALID_INPUT;
    }

    /* Kiểm tra chuỗi rỗng */
    if (is_string_empty(name)) {
        return USER_INVALID_INPUT;
    }

    /* Tìm người dùng */
    user = user_find_by_id(list, user_id);
    if (user == NULL) {
        return USER_NOT_FOUND;
    }

    /* Cập nhật thông tin */
    strncpy(user->name, name, MAX_NAME_LENGTH - 1);
    user->name[MAX_NAME_LENGTH - 1] = '\0';

    return USER_OK;
}

/**
 * \brief           Xóa người dùng khỏi danh sách
 * \param[in,out]   list: Con trỏ tới danh sách người dùng
 * \param[in]       user_id: ID của người dùng cần xóa
 * \return          \ref USER_OK nếu thành công, \ref user_status_t nếu lỗi
 */
user_status_t
user_delete(user_list_t* list, uint32_t user_id) {
    size_t i;

    if (list == NULL) {
        return USER_INVALID_INPUT;
    }

    /* Tìm vị trí người dùng */
    for (i = 0; i < list->count; i++) {
        if (list->users[i].user_id == user_id) {
            /* Kiểm tra người dùng có đang mượn sách */
            if (list->users[i].borrowed_count > 0) {
                return USER_HAS_BORROWED_BOOKS;
            }

            /* Dịch chuyển các phần tử phía sau lên */
            if (i < list->count - 1) {
                memmove(&list->users[i], &list->users[i + 1],
                        (list->count - i - 1) * sizeof(user_t));
            }

            list->count--;
            return USER_OK;
        }
    }

    return USER_NOT_FOUND;
}

/**
 * \brief           Tìm người dùng theo ID
 * \param[in]       list: Con trỏ tới danh sách người dùng
 * \param[in]       user_id: ID của người dùng cần tìm
 * \return          Con trỏ tới người dùng nếu tìm thấy, NULL nếu không tìm thấy
 */
user_t*
user_find_by_id(user_list_t* list, uint32_t user_id) {
    size_t i;

    if (list == NULL) {
        return NULL;
    }

    for (i = 0; i < list->count; i++) {
        if (list->users[i].user_id == user_id) {
            return &list->users[i];
        }
    }

    return NULL;
}

/**
 * \brief           Thêm sách vào danh sách mượn của người dùng
 * \param[in,out]   user: Con trỏ tới người dùng
 * \param[in]       book_id: ID của sách cần thêm
 * \return          \ref USER_OK nếu thành công, \ref user_status_t nếu lỗi
 */
user_status_t
user_add_borrowed_book(user_t* user, uint32_t book_id) {
    if (user == NULL) {
        return USER_INVALID_INPUT;
    }

    /* Kiểm tra đã đạt giới hạn */
    if (user->borrowed_count >= MAX_BORROWED_BOOKS) {
        return USER_BORROW_LIMIT_REACHED;
    }

    /* Thêm sách vào danh sách */
    user->borrowed_books[user->borrowed_count] = book_id;
    user->borrowed_count++;

    return USER_OK;
}

/**
 * \brief           Xóa sách khỏi danh sách mượn của người dùng
 * \param[in,out]   user: Con trỏ tới người dùng
 * \param[in]       book_id: ID của sách cần xóa
 * \return          \ref USER_OK nếu thành công, \ref user_status_t nếu lỗi
 */
user_status_t
user_remove_borrowed_book(user_t* user, uint32_t book_id) {
    size_t i;

    if (user == NULL) {
        return USER_INVALID_INPUT;
    }

    /* Tìm và xóa sách */
    for (i = 0; i < user->borrowed_count; i++) {
        if (user->borrowed_books[i] == book_id) {
            /* Dịch chuyển các phần tử phía sau lên */
            if (i < user->borrowed_count - 1) {
                memmove(&user->borrowed_books[i], &user->borrowed_books[i + 1],
                        (user->borrowed_count - i - 1) * sizeof(uint32_t));
            }

            user->borrowed_count--;
            return USER_OK;
        }
    }

    return USER_BOOK_NOT_BORROWED;
}

/**
 * \brief           Kiểm tra người dùng có đang mượn sách hay không
 * \param[in]       user: Con trỏ tới người dùng
 * \param[in]       book_id: ID của sách cần kiểm tra
 * \return          1 nếu đang mượn, 0 nếu không mượn
 */
uint8_t
user_has_borrowed_book(const user_t* user, uint32_t book_id) {
    size_t i;

    if (user == NULL) {
        return 0;
    }

    for (i = 0; i < user->borrowed_count; i++) {
        if (user->borrowed_books[i] == book_id) {
            return 1;
        }
    }

    return 0;
}

/**
 * \brief           Hiển thị thông tin một người dùng
 * \param[in]       user: Con trỏ tới người dùng cần hiển thị
 */
void
user_display_one(const user_t* user) {
    if (user == NULL) {
        return;
    }

    printf("  %-10u | %-40s | %-15zu\n",
           user->user_id,
           user->name,
           user->borrowed_count);
}

/**
 * \brief           Hiển thị thông tin người dùng kèm danh sách sách đang mượn
 * \param[in]       user: Con trỏ tới người dùng cần hiển thị
 */
void
user_display_with_books(const user_t* user) {
    size_t i;

    if (user == NULL) {
        return;
    }

    printf("\n  ID người dùng: %u\n", user->user_id);
    printf("  Tên: %s\n", user->name);
    printf("  Số sách đang mượn: %zu/%d\n", user->borrowed_count, MAX_BORROWED_BOOKS);

    if (user->borrowed_count > 0) {
        printf("\n  Danh sách sách đang mượn:\n");
        for (i = 0; i < user->borrowed_count; i++) {
            printf("    - ID sách: %u\n", user->borrowed_books[i]);
        }
    } else {
        printf("\n  Chưa mượn sách nào.\n");
    }
}

/**
 * \brief           Hiển thị tất cả người dùng trong danh sách
 * \param[in]       list: Con trỏ tới danh sách người dùng
 */
void
user_display_all(const user_list_t* list) {
    size_t i;

    if (list == NULL || list->count == 0) {
        printf("\n  Danh sách người dùng trống!\n");
        return;
    }

    printf("\n  %-10s | %-40s | %-15s\n", "ID", "Tên", "Số sách mượn");
    print_separator();

    for (i = 0; i < list->count; i++) {
        user_display_one(&list->users[i]);
    }

    printf("\n  Tổng số người dùng: %zu\n", list->count);
}

/**
 * \brief           Đếm tổng số người dùng
 * \param[in]       list: Con trỏ tới danh sách người dùng
 * \return          Tổng số người dùng
 */
size_t
user_count_total(const user_list_t* list) {
    if (list == NULL) {
        return 0;
    }
    return list->count;
}

