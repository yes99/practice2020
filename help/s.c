#include<stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 100


/* 소문자를 대문자로 변환 */
void toUpper(char *in, char *out)
{
    int i;
    for (i = 0; i < strlen(in); i++)
        if (islower(in[i]))
            out[i] = toupper(in[i]);
        else
            out[i] = in[i];
    out[i] = NULL;
}

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



/* 소문자를 대문자로 변환하는 서버 프로그램 */ 
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
            /* 소켓으로부터 한 줄을 읽어 대문자로 변환하여 보냄 */ 
            readLine(cfd, inmsg);
            //toUpper(inmsg, outmsg);
            write(cfd, inmsg, strlen(inmsg) + 1);
            printf("\n처음 받은거 : %s\n", inmsg);
            strcpy(temp, inmsg);
            printf("\ntemp에 잘 저장 되었는가 %s\n", temp);

            fp = fopen(temp, "r");
            
            
            if (fp == NULL)
            {
                write(cfd, "해당 파일 없음", 10);
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
