#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFSIZ 512
int main()
{
    int fd1, fd2, n;
    char buf[BUFSIZ];
    char firstfile[50];    
    if ((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
    {
        perror(argv[2]);
        exit(3);
    }
    while ((n = read(sock_flag, buf, sizeof(buf)) > 0)
            write(fd2, buf, n);
    exit(0);
}