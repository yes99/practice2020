#include <stdio.h>
#include <sys/socket.h>  //socket
#include <netinet/in.h>  //IPPROTO_TCP, sockaddr_in
#include <stdlib.h> //implicit declaration of function exit
#include <string.h> //memset()


#define MAX 128
#define SERVER_PORT 16648
#define PENDING 10

int DATA_SEND_RECV(int);

int main(int argc, char* argv[])
{
    int sock_flag, conn_flag;
    struct sockaddr_in server_addr;

    if((sock_flag = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))<0)
    {
        printf("Socket 생성 실패...\n");
        exit(0);
    }
    else
    {
        printf("Socket 생성 성공 ...\n");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("14.52.175.83");
    server_addr.sin_port = htons(SERVER_PORT);

    if((connect(sock_flag, (struct sockaddr*)&server_addr, sizeof(server_addr)))<0)
    {
        printf("서버 클라이언트 연결 실패...\n");
        exit(0);      
    }
    else
    {
        printf("서버 클라이언트 연결 성공...\n");       
    }

    DATA_SEND_RECV(sock_flag);

    close(sock_flag);
        
}


int DATA_SEND_RECV(int sock_flag)
{
    char buf[MAX];
    int idx;

    //while(true){...}
    while(1)
    {
        printf("Enter the string: ");
        //read(sock_flag, buf, sizeof(buf));
        //printf("From client: %s\nTo client: ", buf;)
        //memset(buf, 0x00, MAX);
        memset(buf, 0x00, MAX);
        fgets(buf, MAX, stdin);

        write(sock_flag, buf, sizeof(buf));
        memset(buf, 0x00, MAX);
        read(sock_flag, buf, sizeof(buf));

        printf("From server: %s\n", buf);
        if(strncmp("exit", buf, 4) == 0)
        {
            printf("서버 종료 ...\n");
            break;
        }

        if(strncmp("exit", buf, 4) == 0)
        {
            printf("서버 종료 ...\n");
            break;
        }
    }

}
