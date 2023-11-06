#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
int main(int argc, char *argv[]) 
{
if (argc != 2) 
{
printf("Hay nhap so duong: \n");
return 1;
}
int n = atoi(argv[1]);
if (n <= 0) 
{
printf("Hay nhap so duong: \n");
return 1;
}
pid_t pid;
int *buffer;
// Tạo bộ nhớ chia sẻ
buffer = mmap(NULL, sizeof(int) * (n + 1), PROT_READ | PROT_WRITE, 
MAP_SHARED | MAP_ANONYMOUS, -1, 0);
pid = fork();
if (pid == 0) 
{ // Tiến trình con
int i = 0;
while (n != 1) 
{
buffer[i++] = n;
if (n % 2 == 0)
n /= 2;
else
n = 3 * n + 1;
}
buffer[i] = n; // Thêm số cuối cùng (1) vào chuỗi
buffer[i + 1] = -1; // Đánh dấu kết thúc chuỗi
} 
else
{ // Tiến trình cha
wait(NULL); // Đợi tiến trình con kết thúc
// In chuỗi
for (int i = 0; buffer[i] != -1; i++)
printf("%d ", buffer[i]);
printf("\n");
// Dọn dẹp bộ nhớ chia sẻ
munmap(buffer, sizeof(int) * (n + 1));
}
return 0;
}