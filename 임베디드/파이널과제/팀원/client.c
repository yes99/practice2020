#include <stdio.h>
#include <sys/socket.h> //socket
#include <netinet/in.h> //IPPROTO_TCP, sockaddr_in
#include <stdlib.h>     //implicit declaration of function exit
#include <string.h>     //memset()
#include <time.h>
#include <memory.h>

#define MAX 128
#define SERVER_PORT 16648
#define PENDING 10

int DATA_SEND_RECV(int);
int BaseBall(int);
int Hangman(int);

int main(int argc, char *argv[])
{
    int sock_flag, conn_flag;
    struct sockaddr_in server_addr;

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
    server_addr.sin_addr.s_addr = inet_addr("192.168.179.128");
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

    //DATA_SEND_RECV(sock_flag);
    //BaseBall(sock_flag);
    Hangman(sock_flag);

    close(sock_flag);
}

int DATA_SEND_RECV(int sock_flag)
{
    char buf[MAX];
    char buf2[MAX];

    int idx;
    int first = 0;
    //while(true){...}
    while (1)
    {
        printf("Enter the string: ");
        //read(sock_flag, buf, sizeof(buf));
        //printf("From client: %s\nTo client: ", buf;)
        //memset(buf, 0x00, MAX);
        if (first == 0)
        {
            memset(buf, 0x00, MAX);
            fgets(buf, MAX, stdin);
            write(sock_flag, buf, sizeof(buf));
            first++;
        }
        else
        {
            while (1)
            {
                memset(buf2, 0x00, MAX);
                fgets(buf2, MAX, stdin);
                if (buf2[0] == buf[strlen(buf) - 2])
                {
                    write(sock_flag, buf2, sizeof(buf));
                    break;
                }
                else
                {
                    printf("\ndo it again\nEnter the string: ");
                }
                
            }
        }
        memset(buf, 0x00, MAX);
        read(sock_flag, buf, sizeof(buf));

        printf("From server: %s\n", buf);
        if (strncmp("exit", buf, 4) == 0)
        {
            printf("서버 종료 ...\n");
            break;
        }
    }
}

int BaseBall(int sock_flag)
{
    int userBall[3];
    int endflag=0;

    char buf[MAX];
    char buf2[MAX];

    memset(buf, 0x00, MAX);
    memset(buf2, 0x00, MAX);



    while (1) // 정상적인 숫자만 입력받기 위한 반복
    {
        read(sock_flag, buf, sizeof(buf));
        printf("%s\n", buf);

        while(1){
                    printf("1부터 9까지의 숫자를 입력하세요 : ");
                    scanf("%d %d %d", &userBall[0], &userBall[1], &userBall[2]);
                    if (userBall[0] < 1 || userBall[0] > 9 || userBall[1] < 1 || userBall[1] > 9 || userBall[2] < 1 || userBall[2] > 9)
                    { // 입력한 숫자가 1 ~ 9 숫자가 아니면 다시 입력받도록
                        printf("범위 외의 숫자를 입력하시면 안됩니다.\n");
                        continue;
                    }
                    else if (userBall[0] == userBall[1] || userBall[0] == userBall[2] || userBall[1] == userBall[2])
                    { // 입력한 숫자 중에 중복된 게 있으면 다시 입력받도록
                        printf("중복된 숫자를 입력하시면 안됩니다.\n");
                        continue;
                    }
                    break; // 아무 문제 없을 경우 반복 종료
        }
        sprintf(buf2,"%d%d%d",userBall[0], userBall[1], userBall[2]);
        write(sock_flag, buf2, sizeof(buf2));

        read(sock_flag, buf, sizeof(buf));
        printf("%s\n", buf);

        read(sock_flag,buf,sizeof(buf));
        endflag=atoi(buf);

        if(endflag==1) {
            printf("게임이 종료되었습니다\n");
            break;
        }
        else continue;
    }
}

int Hangman(int sock_flag)
{
    char buf[MAX];
    char buf2[MAX];
    char ch;
    int endflag=0;

    memset(buf2, 0x00, MAX);
    memset(buf, 0x00, MAX);

    read(sock_flag, buf, sizeof(buf));
    printf("%s\n", buf);

    while(1)
    {
        read(sock_flag, buf, sizeof(buf));
        printf("%s\n", buf);

        printf(" 빈칸에 들어갈 문자 입력 :");
        scanf(" %c", &ch);
        sprintf(buf2,"%c",ch);
        write(sock_flag,buf2,sizeof(buf2));

        read(sock_flag,buf,sizeof(buf));
        endflag=atoi(buf);

        if(endflag==1) {
            read(sock_flag,buf,sizeof(buf));
            printf("%s",buf);
            printf("게임이 종료되었습니다\n");
            break;
        }
        else continue;
    }

}

