# Bài tập lớn môn hệ điều hành
So sánh các phương thức giao tiếp liên tiến trình (IPC) trong hệ điều hành linux
Hệ điều hành sử dụng:
- Kernerl version: Linux version 4.15.0-193-generic
- Ubuntu 18.04.6 LTS

# Phương thức so sánh
- Sử dụng các phương thức giao tiếp liên tiến trình khác nhau để truyền thông tin giữa child và parent process.
- Các trường hợp đo:
  - Truyền một khối dữ liệu lớn 2kB
  - Truyền liên tiếp 512 khối dữ liệu 4B
- Các thông số đo:
  - Thời gian truyền thông điệp: bắt đầu từ lúc process con gửi dữ liệu cho đến khi process cha nhận được hoàn tất dữ liệu.
  - RAM tiêu thụ trong các trường hợp.
