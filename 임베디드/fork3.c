#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int pid1, pid2;
    pid1 = fork();
    if(pid1 == 0)
    {
        printf("[Child 1] : hello, world! pid = %d\n", getpid());
        exit(0);
    }
    pid2 = fork();
    if(pid2==0)
    {
        printf("[Child2] : hello, world ! pid%d\n", getpid());
        exit(0);
    }
    return 0;
}