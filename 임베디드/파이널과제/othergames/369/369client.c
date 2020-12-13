#include <stdio.h>
#include <sys/socket.h> //socket
#include <netinet/in.h> //IPPROTO_TCP, sockaddr_in
#include <stdlib.h>     //implicit declaration of function exit
#include <string.h>     //memset()

#define MAX 128
#define SERVER_PORT 16648
#define PENDING 10

int DATA_SEND_RECV(int);

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
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
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

    DATA_SEND_RECV(sock_flag);

    close(sock_flag);
}

int DATA_SEND_RECV(int sock_flag)
{
    char buf[MAX];
    int idx;
    int a, b, c; //각 1 10 100의자리수
    int ianswer;
    //while(true){...}
    int num;
    int first = 0;
    int cnt; //박수칠 횟수
    char *answer = (char *)malloc(sizeof(char) * 10);
    char *num_string = (char *)malloc(sizeof(char) * 10);
    char temp[100];
    while (1)
    {
        //
        cnt = 0;
        printf("입력하세요: ");

        //보내는 부분
        memset(buf, 0x00, MAX);
        if (first == 0)
        { // 처음 시작하고 싶은 숫자
            printf("처음 시작하고 싶은 숫자: ");
            scanf("%d", &num);
            first++;
        }

        //입력한 수가 숫자가 아닐경우에 대한 대비책도 해야함
        a = num % 10;
        b = (num % 100 - num % 10) / 10;
        c = num / 100;

        if (a % 3 == 0 && a > 0)
            cnt++;
        if (b % 3 == 0 && b > 0)
            cnt++;
        if (c % 3 == 0 && c > 0)
            cnt++;
        printf("1차 연산 완료 cnt = %d", cnt);
        switch (cnt)
        {
        printf("스위치문 진입");
        printf("당신이 보낼 숫자는? :");
        case 0:
            scanf("%d", &ianswer);
            if (ianswer == num)
            {
                printf("정답!\n");
                sprintf(buf, "%d", num+1);
                //strcpy(buf, itoa(num + 1, temp, 10));
                write(sock_flag, buf, sizeof(buf));
                break;
            }
            else
            {
                printf("오답!\n");
                break;
            }
        case 1:
            scanf("%s", answer);
            if (strcmp(answer, "c") == 0)
            {
                sprintf(buf, "%d", num+1);
                // strcpy(buf, itoa(num + 1, temp, 10));
                write(sock_flag, buf, sizeof(buf));
                break;
            }
            else
            {
                printf("오답!\n");
                break;
            }
        case 2:
            scanf("%s", answer);
            if (strcmp(answer, "cc") == 0)
            {
                sprintf(buf, "%d", num+1);
                //strcpy(buf, itoa(num + 1, temp, 10));
                write(sock_flag, buf, sizeof(buf));
                break;
            }
            else
            {
                printf("오답!\n");
                break;
            }
        case 3:
            scanf("%s", answer);
            if (strcmp(answer, "ccc") == 0)
            {
                sprintf(buf, "%d", num+1);                
                //strcpy(buf, itoa(num + 1, temp, 10));
                write(sock_flag, buf, sizeof(buf));
                break;
            }
            else
            {
                printf("오답!\n");
                break;
            }
        }

        //읽는 부분
        memset(buf, 0x00, MAX);
        read(sock_flag, buf, sizeof(buf));
        printf("From server: %s\n", buf);
        num = atoi(buf);

        if (strncmp("exit", buf, 4) == 0)
        {
            printf("서버 종료 ...\n");
            break;
        }
    }
}
