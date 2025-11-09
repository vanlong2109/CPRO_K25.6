# Makefile cho ứng dụng quản lý thư viện
# Copyright (c) 2025 Phạm Văn Long

# Compiler và flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -O2
LDFLAGS =

# Thư mục
SRC_DIR = .
BUILD_DIR = build
BIN_DIR = bin

# Tên file thực thi
TARGET = $(BIN_DIR)/library_management

# Danh sách file nguồn
SRCS = main.c \
       Book/book.c \
       User/user.c \
       Management/management.c \
       Ultils/utils.c

# Danh sách file object
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

# Danh sách file header
HEADERS = Book/book.h \
          User/user.h \
          Management/management.h \
          Ultils/utils.h

# Quy tắc mặc định
.PHONY: all clean run help

all: $(TARGET)

# Tạo file thực thi
$(TARGET): $(OBJS) | $(BIN_DIR)
	@echo "Linking: $@"
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "Build successful!"

# Compile file .c thành .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@echo "Compiling: $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Tạo thư mục build và bin
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)/Book
	@mkdir -p $(BUILD_DIR)/User
	@mkdir -p $(BUILD_DIR)/Management
	@mkdir -p $(BUILD_DIR)/Ultils

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Chạy chương trình
run: $(TARGET)
	@echo "Running application..."
	@./$(TARGET)

# Xóa các file build
clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Clean complete!"

# Hiển thị hướng dẫn
help:
	@echo "Makefile cho ứng dụng quản lý thư viện"
	@echo ""
	@echo "Các lệnh có sẵn:"
	@echo "  make          - Compile toàn bộ project"
	@echo "  make all      - Compile toàn bộ project"
	@echo "  make run      - Compile và chạy ứng dụng"
	@echo "  make clean    - Xóa các file build"
	@echo "  make help     - Hiển thị hướng dẫn này"
	@echo ""
	@echo "Ví dụ:"
	@echo "  make          # Compile project"
	@echo "  make run      # Compile và chạy"
	@echo "  make clean    # Xóa file build"
