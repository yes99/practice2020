
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>  
#define BUFSIZE 512

int main(int argc, char *argv[])
{
    char buffer[BUFSIZE];
    int fd;
    ssize_t nread;
    long total = 0;
    if ((fd = open(argv[1], O_RDONLY)) == -1)
    {
        perror(argv[1]);
        exit(0);
    }
    while ((nread = read(fd, buffer, BUFSIZE)) > 0)
        total += nread;
    close(fd);
    printf("%s file size : %ld byte \n", argv[1], total);
    exit(0);
}