#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid; 
    int getpid();
    int getppid();
    printf("나의 프로세스 번호 : [%d]\n", getpid());
    printf("내 부모 프로세스 번호 : [%d]\n", getppid());
}