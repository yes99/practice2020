#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
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
    {
        cfd = accept(sfd, &clientAddr, &clientlen);
        if (fork() == 0)
        {
            readLine(cfd, inmsg);

            write(cfd, inmsg, strlen(inmsg) + 1);
            printf("\nfirst inms : %s\n", inmsg); //for debug
            strcpy(temp, inmsg);
            printf("\ntemp : %s\n", temp); //for debug

            fp = fopen(temp, "r");

            if (fp == NULL)
            {
                write(cfd, "no file", 10);
            }
            else
            {
                while (fgets(outmsg, MAXLINE, fp) != NULL)
                {
                    printf("exist\n");
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

