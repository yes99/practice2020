#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#define MAX 128
#define PORT 16648
#define PENDING 10
#define CLIENT_SIZE 5

int DATA_SEND_RECV(int);

int main(int argc, char *argv[])
{
    int sock_flag, conn_flag, length;
    struct sockaddr_in server_addr, client_addr;

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
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if ((bind(sock_flag, (struct sockaddr *)&server_addr, sizeof(server_addr))) != 0)
    {
        printf("소켓 바인딩 실패...\n");
        exit(0);
    }
    else
    {
        printf("소켓 바인딩 성공...\n");
    }

    if ((listen(sock_flag, CLIENT_SIZE)) != 0)
    {
        printf("연결대기 실패...\n");
        exit(0);
    }

    length = sizeof(client_addr);

    if ((conn_flag = accept(sock_flag, (struct sockaddr *)&client_addr, &length)) < 0)
    {
        printf("서버 클라이언트 연결 실패...\n");
        exit(0);
    }
    else
    {
        printf("서버 클라이언트 연결 성공...\n");
    }
    

    while(1)
    {
        if(  )
        {
            DATA_SEND_RECV(conn_flag); // 채팅
        }
        else if()
        {
            //369
        }
        else if()
        {
            //끝말잇기            
        }
        else if()
        {
            //숫자야구
        }
        else if()
        {
            //행맨
        }
        else if ()
        {
            break; // 프로그램 완전 끝내기
        }
        
    }
    close(sock_flag);
}

int DATA_SEND_RECV(int conn_flag)
{
    int life = 4;
    char buf[MAX];
    char buf2[MAX];
    int idx;

    //while(true){...}
    while (1)
    {
        memset(buf, 0x00, MAX);
        read(conn_flag, buf, sizeof(buf));
        printf("From client: %s\nTo client: ", buf);
        while (1)
        {
            memset(buf2, 0x00, MAX);
            fgets(buf2, MAX, stdin);
            if (buf2[0] == buf[strlen(buf) - 2])
            {
                write(conn_flag, buf2, sizeof(buf));
                break;
            }
            else
            {
                printf("\ndo it again\nTo client: ");
                life--
            }
            if(life ==0)
            {
                printf("you lose\n");
                break;
            }
        }

        if (strncmp("exit", buf, 4) == 0)
        {
            printf("서버 종료 ...\n");
            break;
        }
    }
}
