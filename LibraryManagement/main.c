/**
 * \file            main.c
 * \brief           Chương trình chính của ứng dụng quản lý thư viện
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

#include <stdio.h>
#include <stdlib.h>
#include "Book/book.h"
#include "User/user.h"
#include "Management/management.h"
#include "Ultils/utils.h"

/* Khai báo các hàm menu */
static void     display_main_menu(void);
static void     handle_book_menu(library_t* library);
static void     handle_user_menu(library_t* library);
static void     handle_borrow_return_menu(library_t* library);
static void     handle_search_menu(library_t* library);
static void     handle_statistics_menu(library_t* library);

/* Khai báo các hàm xử lý sách */
static void     add_book_interactive(book_list_t* books);
static void     update_book_interactive(book_list_t* books);
static void     delete_book_interactive(book_list_t* books);

/* Khai báo các hàm xử lý người dùng */
static void     add_user_interactive(user_list_t* users);
static void     update_user_interactive(user_list_t* users);
static void     delete_user_interactive(user_list_t* users);

/* Khai báo các hàm xử lý mượn/trả */
static void     borrow_book_interactive(library_t* library);
static void     return_book_interactive(library_t* library);

/* Khai báo các hàm tìm kiếm */
static void     search_by_title_interactive(book_list_t* books);
static void     search_by_author_interactive(book_list_t* books);

/**
 * \brief           Hàm main - điểm bắt đầu của chương trình
 * \return          0 nếu thành công
 */
int
main(void) {
    book_list_t books;
    user_list_t users;
    library_t library;
    int32_t choice;
    utils_status_t status;

    /* Khởi tạo hệ thống */
    book_init(&books);
    user_init(&users);
    library.books = &books;
    library.users = &users;

    /* Vòng lặp menu chính */
    while (1) {
        clear_screen();
        display_main_menu();

        status = read_int(&choice, "\n  Nhập lựa chọn của bạn: ");
        if (status != UTILS_OK) {
            printf("\n  Lỗi: Vui lòng nhập số hợp lệ!\n");
            pause_screen();
            continue;
        }

        switch (choice) {
            case 1:
                handle_book_menu(&library);
                break;
            case 2:
                handle_user_menu(&library);
                break;
            case 3:
                handle_borrow_return_menu(&library);
                break;
            case 4:
                handle_search_menu(&library);
                break;
            case 5:
                handle_statistics_menu(&library);
                break;
            case 0:
                printf("\n  Cảm ơn bạn đã sử dụng hệ thống quản lý thư viện!\n");
                return 0;
            default:
                printf("\n  Lỗi: Lựa chọn không hợp lệ!\n");
                pause_screen();
                break;
        }
    }

    return 0;
}

/**
 * \brief           Hiển thị menu chính
 */
static void
display_main_menu(void) {
    print_header("HỆ THỐNG QUẢN LÝ THƯ VIỆN");
    printf("\n");
    printf("  1. Quản lý sách\n");
    printf("  2. Quản lý người dùng\n");
    printf("  3. Mượn/Trả sách\n");
    printf("  4. Tìm kiếm\n");
    printf("  5. Thống kê\n");
    printf("  0. Thoát\n");
    printf("\n");
    print_separator();
}

/**
 * \brief           Xử lý menu quản lý sách
 * \param[in,out]   library: Con trỏ tới cấu trúc thư viện
 */
static void
handle_book_menu(library_t* library) {
    int32_t choice;
    utils_status_t status;

    while (1) {
        clear_screen();
        print_header("QUẢN LÝ SÁCH");
        printf("\n");
        printf("  1. Thêm sách mới\n");
        printf("  2. Cập nhật thông tin sách\n");
        printf("  3. Xóa sách\n");
        printf("  4. Hiển thị tất cả sách\n");
        printf("  5. Hiển thị sách có sẵn\n");
        printf("  0. Quay lại menu chính\n");
        printf("\n");
        print_separator();

        status = read_int(&choice, "\n  Nhập lựa chọn của bạn: ");
        if (status != UTILS_OK) {
            printf("\n  Lỗi: Vui lòng nhập số hợp lệ!\n");
            pause_screen();
            continue;
        }

        switch (choice) {
            case 1:
                add_book_interactive(library->books);
                break;
            case 2:
                update_book_interactive(library->books);
                break;
            case 3:
                delete_book_interactive(library->books);
                break;
            case 4:
                clear_screen();
                print_header("DANH SÁCH TẤT CẢ SÁCH");
                book_display_all(library->books);
                pause_screen();
                break;
            case 5:
                clear_screen();
                print_header("DANH SÁCH SÁCH CÓ SẴN");
                book_display_available(library->books);
                pause_screen();
                break;
            case 0:
                return;
            default:
                printf("\n  Lỗi: Lựa chọn không hợp lệ!\n");
                pause_screen();
                break;
        }
    }
}

/**
 * \brief           Xử lý menu quản lý người dùng
 * \param[in,out]   library: Con trỏ tới cấu trúc thư viện
 */
static void
handle_user_menu(library_t* library) {
    int32_t choice;
    utils_status_t status;

    while (1) {
        clear_screen();
        print_header("QUẢN LÝ NGƯỜI DÙNG");
        printf("\n");
        printf("  1. Thêm người dùng mới\n");
        printf("  2. Cập nhật thông tin người dùng\n");
        printf("  3. Xóa người dùng\n");
        printf("  4. Hiển thị tất cả người dùng\n");
        printf("  5. Xem thông tin chi tiết người dùng\n");
        printf("  0. Quay lại menu chính\n");
        printf("\n");
        print_separator();

        status = read_int(&choice, "\n  Nhập lựa chọn của bạn: ");
        if (status != UTILS_OK) {
            printf("\n  Lỗi: Vui lòng nhập số hợp lệ!\n");
            pause_screen();
            continue;
        }

        switch (choice) {
            case 1:
                add_user_interactive(library->users);
                break;
            case 2:
                update_user_interactive(library->users);
                break;
            case 3:
                delete_user_interactive(library->users);
                break;
            case 4:
                clear_screen();
                print_header("DANH SÁCH TẤT CẢ NGƯỜI DÙNG");
                user_display_all(library->users);
                pause_screen();
                break;
            case 5: {
                uint32_t user_id;
                clear_screen();
                print_header("THÔNG TIN CHI TIẾT NGƯỜI DÙNG");
                status = read_uint(&user_id, "\n  Nhập ID người dùng: ");
                if (status == UTILS_OK) {
                    mgmt_display_user_books(library, user_id);
                } else {
                    printf("\n  Lỗi: ID không hợp lệ!\n");
                }
                pause_screen();
                break;
            }
            case 0:
                return;
            default:
                printf("\n  Lỗi: Lựa chọn không hợp lệ!\n");
                pause_screen();
                break;
        }
    }
}

/**
 * \brief           Xử lý menu mượn/trả sách
 * \param[in,out]   library: Con trỏ tới cấu trúc thư viện
 */
static void
handle_borrow_return_menu(library_t* library) {
    int32_t choice;
    utils_status_t status;

    while (1) {
        clear_screen();
        print_header("MƯỢN/TRẢ SÁCH");
        printf("\n");
        printf("  1. Mượn sách\n");
        printf("  2. Trả sách\n");
        printf("  0. Quay lại menu chính\n");
        printf("\n");
        print_separator();

        status = read_int(&choice, "\n  Nhập lựa chọn của bạn: ");
        if (status != UTILS_OK) {
            printf("\n  Lỗi: Vui lòng nhập số hợp lệ!\n");
            pause_screen();
            continue;
        }

        switch (choice) {
            case 1:
                borrow_book_interactive(library);
                break;
            case 2:
                return_book_interactive(library);
                break;
            case 0:
                return;
            default:
                printf("\n  Lỗi: Lựa chọn không hợp lệ!\n");
                pause_screen();
                break;
        }
    }
}

/**
 * \brief           Xử lý menu tìm kiếm
 * \param[in,out]   library: Con trỏ tới cấu trúc thư viện
 */
static void
handle_search_menu(library_t* library) {
    int32_t choice;
    utils_status_t status;

    while (1) {
        clear_screen();
        print_header("TÌM KIẾM SÁCH");
        printf("\n");
        printf("  1. Tìm kiếm theo tiêu đề\n");
        printf("  2. Tìm kiếm theo tác giả\n");
        printf("  0. Quay lại menu chính\n");
        printf("\n");
        print_separator();

        status = read_int(&choice, "\n  Nhập lựa chọn của bạn: ");
        if (status != UTILS_OK) {
            printf("\n  Lỗi: Vui lòng nhập số hợp lệ!\n");
            pause_screen();
            continue;
        }

        switch (choice) {
            case 1:
                search_by_title_interactive(library->books);
                break;
            case 2:
                search_by_author_interactive(library->books);
                break;
            case 0:
                return;
            default:
                printf("\n  Lỗi: Lựa chọn không hợp lệ!\n");
                pause_screen();
                break;
        }
    }
}

/**
 * \brief           Xử lý menu thống kê
 * \param[in,out]   library: Con trỏ tới cấu trúc thư viện
 */
static void
handle_statistics_menu(library_t* library) {
    clear_screen();
    mgmt_display_statistics(library);
    pause_screen();
}

/**
 * \brief           Thêm sách mới (tương tác với người dùng)
 * \param[in,out]   books: Con trỏ tới danh sách sách
 */
static void
add_book_interactive(book_list_t* books) {
    uint32_t assigned_id;
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    utils_status_t status;
    book_status_t book_status;

    clear_screen();
    print_header("THÊM SÁCH MỚI");

    /* Nhập tiêu đề */
    status = read_string(title, MAX_TITLE_LENGTH, "\n  Nhập tiêu đề sách: ");
    if (status != UTILS_OK) {
        printf("\n  Lỗi: Tiêu đề không hợp lệ!\n");
        pause_screen();
        return;
    }

    /* Nhập tác giả */
    status = read_string(author, MAX_AUTHOR_LENGTH, "  Nhập tên tác giả: ");
    if (status != UTILS_OK) {
        printf("\n  Lỗi: Tên tác giả không hợp lệ!\n");
        pause_screen();
        return;
    }

    /* Thêm sách với ID tự động */
    book_status = book_add(books, title, author, &assigned_id);
    switch (book_status) {
        case BOOK_OK:
            printf("\n  Thành công: Đã thêm sách mới với ID: %u\n", assigned_id);
            break;
        case BOOK_FULL:
            printf("\n  Lỗi: Danh sách sách đã đầy!\n");
            break;
        default:
            printf("\n  Lỗi: Không thể thêm sách!\n");
            break;
    }

    pause_screen();
}

/**
 * \brief           Cập nhật thông tin sách (tương tác với người dùng)
 * \param[in,out]   books: Con trỏ tới danh sách sách
 */
static void
update_book_interactive(book_list_t* books) {
    uint32_t book_id;
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    utils_status_t status;
    book_status_t book_status;

    clear_screen();
    print_header("CẬP NHẬT THÔNG TIN SÁCH");

    /* Nhập ID sách */
    status = read_uint(&book_id, "\n  Nhập ID sách cần cập nhật: ");
    if (status != UTILS_OK) {
        printf("\n  Lỗi: ID không hợp lệ!\n");
        pause_screen();
        return;
    }

    /* Nhập tiêu đề mới */
    status = read_string(title, MAX_TITLE_LENGTH, "  Nhập tiêu đề mới: ");
    if (status != UTILS_OK) {
        printf("\n  Lỗi: Tiêu đề không hợp lệ!\n");
        pause_screen();
        return;
    }

    /* Nhập tác giả mới */
    status = read_string(author, MAX_AUTHOR_LENGTH, "  Nhập tên tác giả mới: ");
    if (status != UTILS_OK) {
        printf("\n  Lỗi: Tên tác giả không hợp lệ!\n");
        pause_screen();
        return;
    }

    /* Cập nhật sách */
    book_status = book_update(books, book_id, title, author);
    switch (book_status) {
        case BOOK_OK:
            printf("\n  Thành công: Đã cập nhật thông tin sách!\n");
            break;
        case BOOK_NOT_FOUND:
            printf("\n  Lỗi: Không tìm thấy sách với ID %u!\n", book_id);
            break;
        default:
            printf("\n  Lỗi: Không thể cập nhật sách!\n");
            break;
    }

    pause_screen();
}

/**
 * \brief           Xóa sách (tương tác với người dùng)
 * \param[in,out]   books: Con trỏ tới danh sách sách
 */
static void
delete_book_interactive(book_list_t* books) {
    uint32_t book_id;
    utils_status_t status;
    book_status_t book_status;

    clear_screen();
    print_header("XÓA SÁCH");

    /* Nhập ID sách */
    status = read_uint(&book_id, "\n  Nhập ID sách cần xóa: ");
    if (status != UTILS_OK) {
        printf("\n  Lỗi: ID không hợp lệ!\n");
        pause_screen();
        return;
    }

    /* Xóa sách */
    book_status = book_delete(books, book_id);
    switch (book_status) {
        case BOOK_OK:
            printf("\n  Thành công: Đã xóa sách!\n");
            break;
        case BOOK_NOT_FOUND:
            printf("\n  Lỗi: Không tìm thấy sách với ID %u!\n", book_id);
            break;
        case BOOK_IS_BORROWED:
            printf("\n  Lỗi: Không thể xóa sách đang được mượn!\n");
            break;
        default:
            printf("\n  Lỗi: Không thể xóa sách!\n");
            break;
    }

    pause_screen();
}

/**
 * \brief           Thêm người dùng mới (tương tác với người dùng)
 * \param[in,out]   users: Con trỏ tới danh sách người dùng
 */
static void
add_user_interactive(user_list_t* users) {
    uint32_t assigned_id;
    char name[MAX_NAME_LENGTH];
    utils_status_t status;
    user_status_t user_status;

    clear_screen();
    print_header("THÊM NGƯỜI DÙNG MỚI");

    /* Nhập tên */
    status = read_string(name, MAX_NAME_LENGTH, "\n  Nhập tên người dùng: ");
    if (status != UTILS_OK) {
        printf("\n  Lỗi: Tên không hợp lệ!\n");
        pause_screen();
        return;
    }

    /* Thêm người dùng với ID tự động */
    user_status = user_add(users, name, &assigned_id);
    switch (user_status) {
        case USER_OK:
            printf("\n  Thành công: Đã thêm người dùng mới với ID: %u\n", assigned_id);
            break;
        case USER_FULL:
            printf("\n  Lỗi: Danh sách người dùng đã đầy!\n");
            break;
        default:
            printf("\n  Lỗi: Không thể thêm người dùng!\n");
            break;
    }

    pause_screen();
}

/**
 * \brief           Cập nhật thông tin người dùng (tương tác với người dùng)
 * \param[in,out]   users: Con trỏ tới danh sách người dùng
 */
static void
update_user_interactive(user_list_t* users) {
    uint32_t user_id;
    char name[MAX_NAME_LENGTH];
    utils_status_t status;
    user_status_t user_status;

    clear_screen();
    print_header("CẬP NHẬT THÔNG TIN NGƯỜI DÙNG");

    /* Nhập ID người dùng */
    status = read_uint(&user_id, "\n  Nhập ID người dùng cần cập nhật: ");
    if (status != UTILS_OK) {
        printf("\n  Lỗi: ID không hợp lệ!\n");
        pause_screen();
        return;
    }

    /* Nhập tên mới */
    status = read_string(name, MAX_NAME_LENGTH, "  Nhập tên mới: ");
    if (status != UTILS_OK) {
        printf("\n  Lỗi: Tên không hợp lệ!\n");
        pause_screen();
        return;
    }

    /* Cập nhật người dùng */
    user_status = user_update(users, user_id, name);
    switch (user_status) {
        case USER_OK:
            printf("\n  Thành công: Đã cập nhật thông tin người dùng!\n");
            break;
        case USER_NOT_FOUND:
            printf("\n  Lỗi: Không tìm thấy người dùng với ID %u!\n", user_id);
            break;
        default:
            printf("\n  Lỗi: Không thể cập nhật người dùng!\n");
            break;
    }

    pause_screen();
}

/**
 * \brief           Xóa người dùng (tương tác với người dùng)
 * \param[in,out]   users: Con trỏ tới danh sách người dùng
 */
static void
delete_user_interactive(user_list_t* users) {
    uint32_t user_id;
    utils_status_t status;
    user_status_t user_status;

    clear_screen();
    print_header("XÓA NGƯỜI DÙNG");

    /* Nhập ID người dùng */
    status = read_uint(&user_id, "\n  Nhập ID người dùng cần xóa: ");
    if (status != UTILS_OK) {
        printf("\n  Lỗi: ID không hợp lệ!\n");
        pause_screen();
        return;
    }

    /* Xóa người dùng */
    user_status = user_delete(users, user_id);
    switch (user_status) {
        case USER_OK:
            printf("\n  Thành công: Đã xóa người dùng!\n");
            break;
        case USER_NOT_FOUND:
            printf("\n  Lỗi: Không tìm thấy người dùng với ID %u!\n", user_id);
            break;
        case USER_HAS_BORROWED_BOOKS:
            printf("\n  Lỗi: Không thể xóa người dùng đang mượn sách!\n");
            break;
        default:
            printf("\n  Lỗi: Không thể xóa người dùng!\n");
            break;
    }

    pause_screen();
}

/**
 * \brief           Mượn sách (tương tác với người dùng)
 * \param[in,out]   library: Con trỏ tới cấu trúc thư viện
 */
static void
borrow_book_interactive(library_t* library) {
    uint32_t user_id;
    uint32_t book_id;
    utils_status_t status;
    mgmt_status_t mgmt_status;

    clear_screen();
    print_header("MƯỢN SÁCH");

    /* Nhập ID người dùng */
    status = read_uint(&user_id, "\n  Nhập ID người dùng: ");
    if (status != UTILS_OK) {
        printf("\n  Lỗi: ID người dùng không hợp lệ!\n");
        pause_screen();
        return;
    }

    /* Nhập ID sách */
    status = read_uint(&book_id, "  Nhập ID sách cần mượn: ");
    if (status != UTILS_OK) {
        printf("\n  Lỗi: ID sách không hợp lệ!\n");
        pause_screen();
        return;
    }

    /* Thực hiện mượn sách */
    mgmt_status = mgmt_borrow_book(library, user_id, book_id);
    switch (mgmt_status) {
        case MGMT_OK:
            printf("\n  Thành công: Đã mượn sách!\n");
            break;
        case MGMT_USER_NOT_FOUND:
            printf("\n  Lỗi: Không tìm thấy người dùng với ID %u!\n", user_id);
            break;
        case MGMT_BOOK_NOT_FOUND:
            printf("\n  Lỗi: Không tìm thấy sách với ID %u!\n", book_id);
            break;
        case MGMT_BOOK_ALREADY_BORROWED:
            printf("\n  Lỗi: Sách đã được mượn!\n");
            break;
        case MGMT_USER_LIMIT_REACHED:
            printf("\n  Lỗi: Người dùng đã mượn đủ %d sách!\n", MAX_BORROWED_BOOKS);
            break;
        default:
            printf("\n  Lỗi: Không thể mượn sách!\n");
            break;
    }

    pause_screen();
}

/**
 * \brief           Trả sách (tương tác với người dùng)
 * \param[in,out]   library: Con trỏ tới cấu trúc thư viện
 */
static void
return_book_interactive(library_t* library) {
    uint32_t user_id;
    uint32_t book_id;
    utils_status_t status;
    mgmt_status_t mgmt_status;

    clear_screen();
    print_header("TRẢ SÁCH");

    /* Nhập ID người dùng */
    status = read_uint(&user_id, "\n  Nhập ID người dùng: ");
    if (status != UTILS_OK) {
        printf("\n  Lỗi: ID người dùng không hợp lệ!\n");
        pause_screen();
        return;
    }

    /* Nhập ID sách */
    status = read_uint(&book_id, "  Nhập ID sách cần trả: ");
    if (status != UTILS_OK) {
        printf("\n  Lỗi: ID sách không hợp lệ!\n");
        pause_screen();
        return;
    }

    /* Thực hiện trả sách */
    mgmt_status = mgmt_return_book(library, user_id, book_id);
    switch (mgmt_status) {
        case MGMT_OK:
            printf("\n  Thành công: Đã trả sách!\n");
            break;
        case MGMT_USER_NOT_FOUND:
            printf("\n  Lỗi: Không tìm thấy người dùng với ID %u!\n", user_id);
            break;
        case MGMT_BOOK_NOT_FOUND:
            printf("\n  Lỗi: Không tìm thấy sách với ID %u!\n", book_id);
            break;
        case MGMT_BOOK_NOT_BORROWED:
            printf("\n  Lỗi: Sách chưa được mượn hoặc không phải người dùng này mượn!\n");
            break;
        default:
            printf("\n  Lỗi: Không thể trả sách!\n");
            break;
    }

    pause_screen();
}

/**
 * \brief           Tìm kiếm sách theo tiêu đề (tương tác với người dùng)
 * \param[in]       books: Con trỏ tới danh sách sách
 */
static void
search_by_title_interactive(book_list_t* books) {
    char title[MAX_TITLE_LENGTH];
    utils_status_t status;

    clear_screen();
    print_header("TÌM KIẾM SÁCH THEO TIÊU ĐỀ");

    /* Nhập tiêu đề cần tìm */
    status = read_string(title, MAX_TITLE_LENGTH, "\n  Nhập tiêu đề cần tìm: ");
    if (status != UTILS_OK) {
        printf("\n  Lỗi: Tiêu đề không hợp lệ!\n");
        pause_screen();
        return;
    }

    /* Tìm kiếm */
    book_search_by_title(books, title);
    pause_screen();
}

/**
 * \brief           Tìm kiếm sách theo tác giả (tương tác với người dùng)
 * \param[in]       books: Con trỏ tới danh sách sách
 */
static void
search_by_author_interactive(book_list_t* books) {
    char author[MAX_AUTHOR_LENGTH];
    utils_status_t status;

    clear_screen();
    print_header("TÌM KIẾM SÁCH THEO TÁC GIẢ");

    /* Nhập tác giả cần tìm */
    status = read_string(author, MAX_AUTHOR_LENGTH, "\n  Nhập tên tác giả cần tìm: ");
    if (status != UTILS_OK) {
        printf("\n  Lỗi: Tên tác giả không hợp lệ!\n");
        pause_screen();
        return;
    }

    /* Tìm kiếm */
    book_search_by_author(books, author);
    pause_screen();
}
