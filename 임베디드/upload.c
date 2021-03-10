#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFSIZ 512
int main(int argc, char *argv[])
{
    int fd1, fd2, n;
    char buf[BUFSIZ];
    char name[50];
    scanf("%s", name);

    if ((fd1 = open(name, O_RDONLY)) ==
        -1)
    {
        perror(argv[1]);
        exit(2);
    }
    if ((fd2 = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
    {
        perror(argv[1]);
        exit(3);
    }
    while ((n = read(fd1, buf, BUFSIZ)) > 0)
        write(fd2, buf, n);
       // printf("%s", buff)
    exit(0);
}