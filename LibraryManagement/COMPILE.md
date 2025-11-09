# Hướng Dẫn Compile Chi Tiết

## Yêu cầu

### Compiler
- **GCC** phiên bản 7.0 trở lên (hỗ trợ C11)
- Hoặc **Clang** phiên bản 6.0 trở lên

### Build Tools
- **GNU Make** 3.81 trở lên

### Hệ điều hành
- Linux (Ubuntu, Debian, Fedora, CentOS, etc.)
- macOS
- Windows (với MinGW hoặc Cygwin)

## Cài đặt Dependencies

### Ubuntu/Debian
```bash
sudo apt update
sudo apt install build-essential
```

### Fedora/CentOS
```bash
sudo dnf install gcc make
# hoặc
sudo yum install gcc make
```

### macOS
```bash
# Cài đặt Xcode Command Line Tools
xcode-select --install
```

### Windows
1. Cài đặt MinGW từ https://www.mingw-w64.org/
2. Hoặc cài đặt Cygwin từ https://www.cygwin.com/

## Compile với Makefile (Khuyến nghị)

### 1. Compile toàn bộ project
```bash
cd LibraryManagement
make
```

Output:
```
Compiling: main.c
Compiling: Book/book.c
Compiling: User/user.c
Compiling: Management/management.c
Compiling: Ultils/utils.c
Linking: bin/library_management
Build successful!
```

### 2. Compile và chạy ngay
```bash
make run
```

### 3. Xóa các file build
```bash
make clean
```

### 4. Rebuild từ đầu
```bash
make clean && make
```

### 5. Xem hướng dẫn
```bash
make help
```

## Compile Thủ công (Không dùng Makefile)

### Linux/macOS

#### Bước 1: Tạo thư mục build
```bash
mkdir -p build/Book build/User build/Management build/Ultils
mkdir -p bin
```

#### Bước 2: Compile từng module
```bash
# Compile utils
gcc -Wall -Wextra -Werror -std=c11 -O2 -c Ultils/utils.c -o build/Ultils/utils.o

# Compile book
gcc -Wall -Wextra -Werror -std=c11 -O2 -c Book/book.c -o build/Book/book.o

# Compile user
gcc -Wall -Wextra -Werror -std=c11 -O2 -c User/user.c -o build/User/user.o

# Compile management
gcc -Wall -Wextra -Werror -std=c11 -O2 -c Management/management.c -o build/Management/management.o

# Compile main
gcc -Wall -Wextra -Werror -std=c11 -O2 -c main.c -o build/main.o
```

#### Bước 3: Link tất cả object files
```bash
gcc -o bin/library_management \
    build/main.o \
    build/Book/book.o \
    build/User/user.o \
    build/Management/management.o \
    build/Ultils/utils.o
```

#### Bước 4: Chạy chương trình
```bash
./bin/library_management
```

### Windows (MinGW)

#### Bước 1: Tạo thư mục build
```cmd
mkdir build\Book build\User build\Management build\Ultils
mkdir bin
```

#### Bước 2: Compile từng module
```cmd
gcc -Wall -Wextra -Werror -std=c11 -O2 -c Ultils\utils.c -o build\Ultils\utils.o
gcc -Wall -Wextra -Werror -std=c11 -O2 -c Book\book.c -o build\Book\book.o
gcc -Wall -Wextra -Werror -std=c11 -O2 -c User\user.c -o build\User\user.o
gcc -Wall -Wextra -Werror -std=c11 -O2 -c Management\management.c -o build\Management\management.o
gcc -Wall -Wextra -Werror -std=c11 -O2 -c main.c -o build\main.o
```

#### Bước 3: Link
```cmd
gcc -o bin\library_management.exe build\main.o build\Book\book.o build\User\user.o build\Management\management.o build\Ultils\utils.o
```

#### Bước 4: Chạy
```cmd
bin\library_management.exe
```

## Compile Flags Giải thích

### `-Wall`
Bật tất cả các cảnh báo phổ biến

### `-Wextra`
Bật thêm các cảnh báo bổ sung

### `-Werror`
Coi tất cả cảnh báo như lỗi (đảm bảo code sạch)

### `-std=c11`
Sử dụng chuẩn C11

### `-O2`
Tối ưu hóa code ở mức độ 2 (cân bằng giữa tốc độ và kích thước)

### `-c`
Compile thành object file (.o) mà không link

### `-o`
Chỉ định tên file output

## Troubleshooting

### Lỗi: "gcc: command not found"
**Giải pháp**: Cài đặt GCC compiler
```bash
# Ubuntu/Debian
sudo apt install gcc

# Fedora/CentOS
sudo dnf install gcc
```

### Lỗi: "make: command not found"
**Giải pháp**: Cài đặt GNU Make
```bash
# Ubuntu/Debian
sudo apt install make

# Fedora/CentOS
sudo dnf install make
```

### Lỗi: "Permission denied"
**Giải pháp**: Cấp quyền thực thi
```bash
chmod +x bin/library_management
```

### Lỗi compile liên quan đến encoding
**Giải pháp**: Đảm bảo file source được lưu với encoding UTF-8

### Lỗi: "undefined reference to..."
**Giải pháp**: Đảm bảo tất cả object files được link đúng thứ tự

## Kiểm tra Version

### Kiểm tra GCC version
```bash
gcc --version
```

Output mong đợi:
```
gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
```

### Kiểm tra Make version
```bash
make --version
```

Output mong đợi:
```
GNU Make 4.3
```

## Cấu trúc Build Output

```
LibraryManagement/
├── build/                  # Thư mục chứa object files
│   ├── main.o
│   ├── Book/
│   │   └── book.o
│   ├── User/
│   │   └── user.o
│   ├── Management/
│   │   └── management.o
│   └── Ultils/
│       └── utils.o
└── bin/                    # Thư mục chứa file thực thi
    └── library_management
```

## Compile cho Debug

Nếu muốn compile với debug symbols:

```bash
gcc -Wall -Wextra -std=c11 -g -O0 -c [source_files]
```

Flags:
- `-g`: Thêm debug symbols
- `-O0`: Không tối ưu hóa (dễ debug hơn)

## Compile cho Production

Nếu muốn compile với tối ưu hóa tối đa:

```bash
gcc -Wall -Wextra -Werror -std=c11 -O3 -c [source_files]
```

Flags:
- `-O3`: Tối ưu hóa tối đa

## Chạy với Valgrind (Memory Check)

```bash
# Compile với debug symbols
make clean
gcc -Wall -Wextra -std=c11 -g -O0 -c main.c -o build/main.o
# ... compile các file khác tương tự
gcc -o bin/library_management build/*.o

# Chạy với valgrind
valgrind --leak-check=full ./bin/library_management
```

---

**Lưu ý**: Makefile đã được cấu hình tối ưu, khuyến nghị sử dụng `make` thay vì compile thủ công.

