#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {
// Kiểm tra xem có đúng một đối số được truyền vào không
if (argc != 2) {
printf("Cách sử dụng: ./time <lệnh>\n");
return 1;
}
struct timeval start, end;
// Lấy thời gian hiện tại và lưu vào biến start
gettimeofday(&start, NULL);
// Tạo một tiến trình con
pid_t pid = fork();
// Nếu đây là tiến trình con
if (pid == 0) {
// Thực thi lệnh được truyền vào từ dòng lệnh
if (execl("/bin/sh", "/bin/sh", "-c", argv[1], NULL) == -1) {
printf("Lỗi: không thể thực thi lệnh\n");
return 1;
}
} 
// Nếu đây là tiến trình cha
else if (pid > 0) {
// Chờ tiến trình con kết thúc
wait(NULL);
// Lấy thời gian hiện tại và lưu vào biến end
gettimeofday(&end, NULL);
// Tính toán thời gian thực thi bằng cách lấy thời gian kết thúc trừ đi thời gian bắt đầu
double ans = (end.tv_sec - start.tv_sec) + ((end.tv_usec -
start.tv_usec)/1000000.0);
// In ra thời gian thực thi
printf("Thời gian thực thi: %.5f giây\n", ans);
} 
// Nếu có lỗi xảy ra khi tạo tiến trình con
else {
printf("Lỗi: không thể tạo tiến trình con\n");
return 1;
}
return 0;
}