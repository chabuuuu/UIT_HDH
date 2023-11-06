/*######################################
# University of Information Technology
# IT007 Operating System 
#
# <Your name>, <your Student ID>
# File: test_shm_B.c 
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
 fd = shm_open(name, O_RDWR,0666);
 /* memory map the shared memory object */
 ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, 
MAP_SHARED, fd, 0);
 /* read from the shared memory object */
 printf("Read shared memory: ");
 printf("%s\n",(char *)ptr);
 /* update the shared memory object */
 strcpy(ptr, "Hello Process A");
 printf("Shared memory updated: %s\n", ptr);
 sleep(5);
 // unmap the shared memory segment and close the file descriptor
 munmap(ptr, SIZE);
 close(fd);
// remove the shared memory segment
 shm_unlink(name);
 return 0;
}