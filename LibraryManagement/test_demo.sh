#!/bin/bash

# Script demo test ứng dụng quản lý thư viện
# Copyright (c) 2025 Phạm Văn Long

echo "=========================================="
echo "DEMO ỨNG DỤNG QUẢN LÝ THƯ VIỆN"
echo "=========================================="
echo ""

# Kiểm tra file thực thi có tồn tại không
if [ ! -f "bin/library_management" ]; then
    echo "Lỗi: File thực thi không tồn tại!"
    echo "Vui lòng chạy 'make' trước khi test."
    exit 1
fi

echo "✓ File thực thi đã sẵn sàng"
echo ""

# Kiểm tra các file source
echo "Kiểm tra cấu trúc project..."
files=(
    "main.c"
    "Book/book.h"
    "Book/book.c"
    "User/user.h"
    "User/user.c"
    "Management/management.h"
    "Management/management.c"
    "Ultils/utils.h"
    "Ultils/utils.c"
    "Makefile"
    "README.md"
)

for file in "${files[@]}"; do
    if [ -f "$file" ]; then
        echo "  ✓ $file"
    else
        echo "  ✗ $file (không tìm thấy)"
    fi
done

echo ""
echo "=========================================="
echo "THÔNG TIN BUILD"
echo "=========================================="
echo ""

# Đếm số dòng code
total_lines=0
for file in main.c Book/*.c User/*.c Management/*.c Ultils/*.c; do
    if [ -f "$file" ]; then
        lines=$(wc -l < "$file")
        total_lines=$((total_lines + lines))
        echo "  $file: $lines dòng"
    fi
done

echo ""
echo "  Tổng số dòng code: $total_lines"
echo ""

echo "=========================================="
echo "HƯỚNG DẪN SỬ DỤNG"
echo "=========================================="
echo ""
echo "Để chạy ứng dụng, sử dụng lệnh:"
echo "  ./bin/library_management"
echo ""
echo "hoặc:"
echo "  make run"
echo ""
echo "Các chức năng chính:"
echo "  1. Quản lý sách (CRUD)"
echo "  2. Quản lý người dùng (CRUD)"
echo "  3. Mượn/Trả sách"
echo "  4. Tìm kiếm sách"
echo "  5. Thống kê"
echo ""
echo "=========================================="
echo "DEMO HOÀN TẤT"
echo "=========================================="

