#include<stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 100



/* 한 줄 읽기 */
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
    int sfd, cfd, clientlen;
    FILE *fp;
    char inmsg[MAXLINE], outmsg[MAXLINE], temp[MAXLINE];
    struct sockaddr_un serverAddr, clientAddr;

    signal(SIGCHLD, SIG_IGN);
    clientlen = sizeof(clientAddr);

    sfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, "convert");
    unlink("convert");
    bind(sfd, &serverAddr, sizeof(serverAddr));

    listen(sfd, 5);

    while (1)
    { /* 소켓 연결 요청 수락 */
        cfd = accept(sfd, &clientAddr, &clientlen);
        if (fork() == 0)
        {
            readLine(cfd, inmsg);
            write(cfd, inmsg, strlen(inmsg) + 1);
            printf("\n처음 받은거 : %s\n", inmsg);
            strcpy(temp, inmsg);
            printf("\ntemp에 잘 저장 되었는가 %s\n", temp);
            temp[strlen(temp)-1] = '\0';
            fp = fopen(temp, "r");
            
            
            if (fp == NULL)
            {
                write(cfd, "no file\n", 10);
                printf("there's no file\n");
            }
            else
            { /* 파일에서 한 줄씩 읽어 소켓을 통해 보낸다 */
                while (fgets(outmsg, MAXLINE, fp) != NULL)
                {
                    printf("존재한다\n");
                    write(cfd, outmsg, strlen(outmsg) + 1);
                }
            }
            close(cfd);
            exit(0);
        }
        else
            close(cfd);
    }
}
