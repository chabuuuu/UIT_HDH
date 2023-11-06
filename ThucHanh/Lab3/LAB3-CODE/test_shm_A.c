/*######################################
# University of Information Technology
# IT007 Operating System 
#
# <Your name>, <your Student ID>
# File: test_shm_A.c 
######################################*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
int main()
{
 /* the size (in bytes) of shared memory object */
 const int SIZE = 4096;
 /* name of the shared memory object */
 const char *name = "OS";
 /* shared memory file descriptor */
 int fd;
 /* pointer to shared memory obect */
 char *ptr;
 /* create the shared memory object */
 fd = shm_open(name, O_CREAT | O_RDWR,0666);
 /* configure the size of the shared memory object */
 ftruncate(fd, SIZE);
 /* memory map the shared memory object */
 ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, 
MAP_SHARED, fd, 0);
 /* write to the shared memory object */
 strcpy(ptr, "Hello Process B");
/* wait until Process B updates the shared memory 
segment */
 while (strncmp(ptr, "Hello Process B", 15) == 0)
 {
 printf("Waiting Process B update shared memory\n");
 sleep(1);
 }
 printf("Memory updated: %s\n", (char *)ptr);
 /* unmap the shared memory segment and close the 
file descriptor */
 munmap(ptr, SIZE);
 close(fd);
 return 0;
}