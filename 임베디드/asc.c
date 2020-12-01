#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 100
void readLine(int fd, char *str)
{
    int n;
    do
    {
        n = read(fd, str, 1);
    } while (n > 0 && *str++ != '\0');

    return (n > 0);
}

int main()
{
    int cfd, result;
    char inmsg[MAXLINE], outmsg[MAXLINE];
    struct sockaddr_un serverAddr;

    cfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, "convert");
    
    do
    { /* 연결 요청 */
        result = connect(cfd, &serverAddr, sizeof(serverAddr));
        if (result == -1)
        {
            sleep(1);
        }
    } while (result == -1);
    printf("연결 요청 성공\n");
    printf("파일 이름 입력:");
    scanf("% s", inmsg);
    printf("입력 성공\n");
    write(cfd, inmsg, strlen(inmsg) + 1);
    printf("%d",write(cfd, inmsg, strlen(inmsg) + 1));
    /* 소켓으로부터 파일 내용 읽어서 프린트 */
    while (readLine(cfd, outmsg))
        printf("%s", outmsg);
    close(cfd);
    exit(0);
}

