#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
int main() {
const int BUFFER_SIZE = 10; // Định nghĩa kích thước buffer
const char *name = "OS"; // Tên của shared memory object
// Tạo shared memory object
int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
// Cấu hình kích thước của shared memory object
ftruncate(shm_fd, sizeof(int) * (BUFFER_SIZE + 1));
// Mapping shared memory object
int *buffer = mmap(0, sizeof(int) * (BUFFER_SIZE + 1), PROT_READ | 
PROT_WRITE, MAP_SHARED, shm_fd, 0);
// Kiểm tra xem mmap có thành công không
if (buffer == MAP_FAILED) {
perror("mmap");
return 1;
}
int *sum = buffer + BUFFER_SIZE; // Lưu tổng vào cuối buffer
*sum = 0; // Khởi tạo tổng bằng 0
pid_t pid = fork(); // Tạo một tiến trình con
if (pid == 0) { // Tiến trình con (Consumer)
while (*sum <= 100) { // Chạy cho đến khi tổng lớn hơn 100
for (int i = 0; i < BUFFER_SIZE; i++) { // Duyệt qua từng phần tử trong buffer
if (buffer[i] != 0) { // Nếu phần tử không rỗng
printf("Consumer reads %d\n", buffer[i]); // In ra giá trị phần tử
*sum += buffer[i]; // Cộng giá trị phần tử vào tổng
buffer[i] = 0; // Đặt lại giá trị phần tử thành 0
}
}
}
printf("Sum > 100, Consumer stops\n"); // In ra thông báo khi tổng lớn hơn 100
} else if (pid > 0) { // Tiến trình cha (Producer)
while (*sum <= 100) { // Chạy cho đến khi tổng lớn hơn 100
for (int i = 0; i < BUFFER_SIZE; i++) { // Duyệt qua từng phần tử trong buffer
if (buffer[i] == 0) { // Nếu phần tử rỗng
buffer[i] = rand() % 11 + 10; // Tạo một số ngẫu nhiên trong khoảng [10,20] và gán vào phần tử
printf("Producer writes %d\n", buffer[i]); // In ra giá trị đã ghi vào phần tử
}
}
}
printf("Sum > 100, Producer stops\n"); // In ra thông báo khi tổng lớn hơn 100
wait(NULL); // Đợi tiến trình con kết thúc trước khi tiến trình cha kết thúc
// Xóa shared memory object
shm_unlink(name);
} else { // fork failed
perror("fork");
return 1;
}
return 0;
}