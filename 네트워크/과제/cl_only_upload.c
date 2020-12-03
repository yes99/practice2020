#include <stdio.h>
#include <sys/socket.h> //socket
#include <netinet/in.h> //IPPROTO_TCP, sockaddr_in
#include <stdlib.h>     //implicit declaration of function exit
#include <string.h>     //memset()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 128
#define SERVER_PORT 45000
#define PENDING 10

int DATA_SEND_RECV(int sock_flag, char stid[]);
int main(int argc, char *argv[])
{
    char message[256], stid[12];
    int sock_flag, conn_flag;
    struct sockaddr_in server_addr;
    strcpy(stid, argv[0]);
    if ((sock_flag = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("Socket 생성 실패...\n");
        exit(0);
    }
    else
    {
        printf("Socket 생성 성공 ...\n");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("210.94.172.185");
    server_addr.sin_port = htons(SERVER_PORT);

    if ((connect(sock_flag, (struct sockaddr *)&server_addr, sizeof(server_addr))) < 0)
    {
        printf("서버 클라이언트 연결 실패...\n");
        exit(0);
    }
    else
    {
        printf("서버 클라이언트 연결 성공...\n");
    }

    DATA_SEND_RECV(sock_flag, stid);

    close(sock_flag);
}

int DATA_SEND_RECV(int sock_flag, char stid[])
{
    char buf[MAX];
    int idx;
    char flag[15];
    char data[200];
    char temp[200];
    char file[50];
    char buff[200];
    int fd;
    ssize_t rd_size;
    scanf("%s", file);
    if ((fd = open(file, O_RDONLY)) > 0)
    {
        while ((rd_size = read(fd, buff, 200 - 1)) > 0)
        {                         //  4 byte씩 읽씁니다.
            buff[rd_size] = '\0'; // puts()를 위해 NULL을 대입
            memset(buf, 0x00, MAX);
            strcpy(buf, "FLAG_UPLOAD|");
            strcat(buf, stid);
            strcat(buf, "|");
            strcat(buf, buff);
            printf("전송한 문자는 %s", buf);
            write(sock_flag, buf, sizeof(buf));
        }
        memset(buf, 0x00, MAX);
        strcpy(buf, "FLAG_UPLOAD|");
        strcat(buf, stid);
        strcat(buf, "|");
        strcat(buf, "EOF");
        write(sock_flag, buf, sizeof(buf));
        memset(buf, 0x00, MAX);
        read(sock_flag, buf, sizeof(buf));
        printf("From server: %s\n", buf);
        close(fd);
    }
    else
    {
        printf("파일 열기에 실패했습니다.\n");
    }
}
