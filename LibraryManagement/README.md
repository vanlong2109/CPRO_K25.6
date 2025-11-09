# Hệ Thống Quản Lý Thư Viện

Ứng dụng quản lý thư viện hoàn chỉnh được viết bằng ngôn ngữ C, tuân thủ nghiêm ngặt các nguyên tắc Clean Code và C Coding Convention.

## Tác giả

**Phạm Văn Long** - CPRO_K25.6

## Tính năng

### 1. Quản lý Sách
- ✅ Thêm sách mới với thông tin: ID, tiêu đề, tác giả
- ✅ Cập nhật thông tin sách
- ✅ Xóa sách (chỉ khi sách chưa được mượn)
- ✅ Hiển thị danh sách tất cả sách
- ✅ Hiển thị danh sách sách có sẵn
- ✅ Validation đầy đủ: ID duy nhất, tiêu đề và tác giả không rỗng

### 2. Quản lý Người dùng
- ✅ Thêm người dùng mới với thông tin: ID, tên
- ✅ Cập nhật thông tin người dùng
- ✅ Xóa người dùng (chỉ khi người dùng chưa mượn sách)
- ✅ Hiển thị danh sách tất cả người dùng
- ✅ Xem thông tin chi tiết người dùng kèm danh sách sách đang mượn
- ✅ Validation đầy đủ: ID duy nhất, tên không rỗng

### 3. Quản lý Mượn/Trả Sách
- ✅ Mượn sách với các điều kiện:
  - Sách tồn tại và chưa được mượn
  - Người dùng tồn tại
  - Người dùng chưa đạt giới hạn (tối đa 5 cuốn)
- ✅ Trả sách và cập nhật trạng thái
- ✅ Theo dõi số lượng sách mỗi người dùng đang mượn

### 4. Tìm kiếm
- ✅ Tìm kiếm sách theo tiêu đề (hỗ trợ tìm kiếm một phần, không phân biệt hoa thường)
- ✅ Tìm kiếm sách theo tác giả (hỗ trợ tìm kiếm một phần, không phân biệt hoa thường)

### 5. Thống kê
- ✅ Tổng số sách trong thư viện
- ✅ Số sách đang được mượn
- ✅ Số sách có sẵn
- ✅ Tổng số người dùng

## Cấu trúc Project

```
LibraryManagement/
├── Book/
│   ├── book.h              # Header file quản lý sách
│   └── book.c              # Implementation quản lý sách
├── User/
│   ├── user.h              # Header file quản lý người dùng
│   └── user.c              # Implementation quản lý người dùng
├── Management/
│   ├── management.h        # Header file quản lý mượn/trả
│   └── management.c        # Implementation quản lý mượn/trả
├── Ultils/
│   ├── utils.h             # Header file tiện ích
│   └── utils.c             # Implementation tiện ích
├── main.c                  # File chính của chương trình
├── Makefile                # Build system
└── README.md               # Tài liệu hướng dẫn
```

## Yêu cầu Hệ thống

- **Compiler**: GCC (hỗ trợ C11 trở lên)
- **OS**: Linux, macOS, hoặc Windows (với MinGW/Cygwin)
- **Make**: GNU Make

## Hướng dẫn Compile

### Compile toàn bộ project

```bash
cd LibraryManagement
make
```

### Compile và chạy ngay

```bash
make run
```

### Xóa các file build

```bash
make clean
```

### Xem hướng dẫn

```bash
make help
```

## Hướng dẫn Sử dụng

### Chạy ứng dụng

```bash
./bin/library_management
```

hoặc

```bash
make run
```

### Menu chính

Khi chạy ứng dụng, bạn sẽ thấy menu chính với các lựa chọn:

```
================================================================================
  HỆ THỐNG QUẢN LÝ THƯ VIỆN
================================================================================

  1. Quản lý sách
  2. Quản lý người dùng
  3. Mượn/Trả sách
  4. Tìm kiếm
  5. Thống kê
  0. Thoát
```

### Ví dụ Sử dụng

#### 1. Thêm sách mới
- Chọn `1` (Quản lý sách)
- Chọn `1` (Thêm sách mới)
- Nhập ID sách (ví dụ: `1001`)
- Nhập tiêu đề (ví dụ: `Clean Code`)
- Nhập tác giả (ví dụ: `Robert C. Martin`)

#### 2. Thêm người dùng
- Chọn `2` (Quản lý người dùng)
- Chọn `1` (Thêm người dùng mới)
- Nhập ID người dùng (ví dụ: `2001`)
- Nhập tên (ví dụ: `Nguyễn Văn A`)

#### 3. Mượn sách
- Chọn `3` (Mượn/Trả sách)
- Chọn `1` (Mượn sách)
- Nhập ID người dùng (ví dụ: `2001`)
- Nhập ID sách (ví dụ: `1001`)

#### 4. Tìm kiếm sách
- Chọn `4` (Tìm kiếm)
- Chọn `1` (Tìm kiếm theo tiêu đề)
- Nhập từ khóa (ví dụ: `clean`)

## Đặc điểm Kỹ thuật

### Clean Code Principles
- ✅ Single Responsibility Principle: Mỗi hàm chỉ thực hiện một nhiệm vụ
- ✅ Tách biệt logic thành các module rõ ràng
- ✅ Đặt tên biến, hàm theo convention: `snake_case`
- ✅ Giới hạn độ dài hàm tối đa 50 dòng code
- ✅ Comment đầy đủ bằng tiếng Việt

### C Coding Convention
- ✅ Tuân thủ theo tiêu chuẩn tại https://github.com/MaJerle/c-code-style
- ✅ Sử dụng C11 standard
- ✅ Không sử dụng tabs, dùng 4 spaces
- ✅ Header guards cho tất cả file .h
- ✅ Doxygen documentation style

### Memory Management
- ✅ Sử dụng static arrays để tránh memory leak
- ✅ Không có dynamic memory allocation (malloc/free)
- ✅ Bounds checking cho tất cả array access

### Error Handling
- ✅ Validation đầy đủ cho tất cả input
- ✅ Thông báo lỗi rõ ràng bằng tiếng Việt
- ✅ Xử lý tất cả edge cases
- ✅ Không crash trong mọi tình huống

## Giới hạn

- Tối đa 1000 sách
- Tối đa 500 người dùng
- Mỗi người dùng tối đa mượn 5 cuốn sách
- ID hợp lệ: từ 1 đến 999999
- Độ dài tiêu đề/tên: tối đa 256 ký tự

## License

MIT License - Copyright (c) 2025 Phạm Văn Long

## Liên hệ

Nếu có bất kỳ câu hỏi hoặc góp ý nào, vui lòng liên hệ qua repository.

---

**Lưu ý**: Đây là project học tập, được xây dựng với mục đích thực hành Clean Code và C Coding Convention.

