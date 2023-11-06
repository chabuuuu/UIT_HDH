/*######################################
# University of Information Technology
# IT007 Operating System 
#
# <Your name>, <your Student ID>
# File: test_execl.c 
#
######################################*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
int main(int argc, char* argv[])
{
 __pid_t pid;
 pid = fork();
 if (pid > 0)
 {
 printf("PARENTS | PID = %ld | PPID = %ld\n", 
(long)getpid(), (long)getppid());
 if (argc > 2)
 printf("PARENTS | There are %d arguments\n", 
argc - 1);
 wait(NULL);
 }
 if (pid == 0)
 {
 execl("./count.sh", "./count.sh", "10", NULL);
 
 printf("CHILDREN | PID = %ld | PPID = %ld\n", 
(long)getpid(), (long)getppid());
 printf("CHILDREN | List of arguments: \n");
 for (int i = 1; i < argc; i++)
 {
 printf("%s\n", argv[i]);
 }
 }
exit(0);
}