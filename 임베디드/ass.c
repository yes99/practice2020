#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 100

/* 한 줄 읽기 */
int readLine(int fd, char *str)
{
    int n;
    do
    {
        n = read(fd, str, 1);
    } while (n > 0 && *str++ != '\0');
    return (n > 0);
}


/* 소문자를 대문자로 변환하는 서버 프로그램 */
int main()
{
    int sfd, cfd, clientlen;
    FILE *fp;
    char inmsg[MAXLINE], outmsg[MAXLINE];
    struct sockaddr_un serverAddr, clientAddr;
    int pid;
    signal(SIGCHLD, SIG_IGN);
    clientlen = sizeof(clientAddr);

    sfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, "convert");
    unlink("convert");
    bind(sfd, &serverAddr, sizeof(serverAddr));
    printf("바인드 성공\n");
    listen(sfd, 5);
    printf("리슨 성공\n");
    while (1)
    { /* 소켓 연결 요청 수락 */
        printf("연결요청 수락 아직아직아직\n");
        cfd = accept(sfd, &clientAddr, &clientlen);
        printf("연결요청 수락\n");

        if (fork() == 0)
        {
            readLine(cfd, inmsg);
            fp = fopen(inmsg, "r");
            if (fp == NULL)
            {
                write(cfd, "해당 파일 없음", 10);
            }
            else
            { /* 파일에서 한 줄씩 읽어 소켓을 통해 보낸다 */
                printf("해당 파일 존재\n");
                while (fgets(inmsg, MAXLINE, fp) != NULL)
                {
                    write(cfd, inmsg, strlen(inmsg) + 1);
                }
            }
            close(cfd);
            exit(0);
        }
        else
            close(cfd);
    }
}

