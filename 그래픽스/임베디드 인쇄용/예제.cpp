#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
    int fd;
    int i, buf;
    fd = open("num.dat", O_RDWR | O_CREAT);
    if (fd < 0)
    {
        perror("error : ");
        exit(0);
    }
    for (i = 1000; i < 1010; i++)
    {
        write(fd, (void*)&i, sizeof(i));
    }
    // ������ ó������ �̵��� ���� �����͸� �д´�.
    lseek(fd, 0, SEEK_SET);
    read(fd, (void*)&buf, sizeof(i));
    printf("%d\n", buf);

    // ������ ó���̷� �̵��� ���� 4��° �Էµ� ���ڸ�
    // �д´�.
    lseek(fd, 4 * sizeof(i), SEEK_SET);
    read(fd, (void*)&buf, sizeof(i));
    printf("%d\n", buf);
}