# Smart Plant Watering System (SPWS)

Ứng dụng nhúng mô phỏng hệ thống tưới cây tự động: đọc cảm biến (độ ẩm đất, nhiệt độ), quyết định bật/tắt bơm theo ngưỡng cấu hình, cho phép chuyển chế độ AUTO/MANUAL và tưới tay, đồng thời cập nhật LED và in log trạng thái.

## Cấu trúc thư mục (mã nằm trong `spws/`)
- `spws/config.h`: Enum/struct/hằng số cấu hình dùng chung (ngưỡng độ ẩm, thời gian tưới, interval đọc cảm biến).
- `spws/main.c`: Vòng lặp chính, xử lý nút, đọc cảm biến, chọn logic theo chế độ và gọi HAL.
- `spws/spws_controller/`: Logic điều khiển thuần (không đụng phần cứng), gồm init mặc định, AUTO, MANUAL, stop và áp dụng output.
- `spws/hal_library/`: Lớp mô phỏng phần cứng: cảm biến, nút nhấn, bơm, LED. Có thể thay thế bằng driver thật khi lên board.
- `Makefile`: Biên dịch/ch dọn/ chạy nhanh từ thư mục gốc repo.

## Yêu cầu build
- GCC hỗ trợ C11.

## Cách build và chạy nhanh
```bash
make               # biên dịch ra binary spws/spws
./spws/spws        # chạy mô phỏng
make clean         # dọn file .o và binary
```

## Ghi chú mô phỏng
- Lịch nhấn nút (giây kể từ khi khởi động): nút chuyển chế độ tại 15s và 40s; nút tưới tay tại 18s và 22s (chỉ hiệu lực khi đang MANUAL).
- Cảm biến độ ẩm tuần tự lấy giá trị từ mảng mẫu để kiểm thử logic khởi động/tắt bơm.
- LED: GREEN bình thường, YELLOW đang tưới, RED dành cho cảnh báo (chưa dùng ở mô phỏng), OFF khi khởi động.
- Ngưỡng mặc định: bật bơm khi <35%, tắt khi >65% hoặc quá 20s (AUTO); tưới tay 10s khi nhấn nút (MANUAL).

## Lên phần cứng thật
- Thay thế các hàm trong `hal_library/` bằng đọc ADC, GPIO, timer thực tế.
- Giữ nguyên API để không phải sửa logic ở `main.c` và `spws_controller/`.
