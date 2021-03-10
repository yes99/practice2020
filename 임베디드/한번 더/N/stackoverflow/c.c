#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 100

int readLine(int fd, char *str)
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
    { 
        result = connect(cfd, &serverAddr, sizeof(serverAddr));
        if (result == -1)
            sleep(1);
    } while (result == -1);

    printf("File name:\n");
    fgets(inmsg, MAXLINE, stdin);
    write(cfd, inmsg, strlen(inmsg) + 1); 
    readLine(cfd, outmsg);
    printf("%s --> \n%s\n", inmsg, outmsg); //for debug
    readLine(cfd, outmsg);
    printf("%s", outmsg); //for debug
    
    while (readLine(cfd, outmsg))
        printf("%s", outmsg);
    close(cfd);
    exit(0);
    
    
    close(cfd);
    exit(0);
}