#include <stdio.h>
#include <sys/socket.h> //socket
#include <netinet/in.h> //IPPROTO_TCP, sockaddr_in
#include <stdlib.h>     //implicit declaration of function exit
#include <string.h>     //memset()

#define MAX 128
#define SERVER_PORT 16648
#define PENDING 10

//클라이언트

int DATA_SEND_RECV(int sock_flag)
{
    char buf[MAX];
    int idx;
    //while(true){...}
    int num;
    int first = 0;

    while (1)
    {
        //

        printf("입력하세요: ");

        //보내는 부분
        memset(buf, 0x00, MAX);
        if (first == 0)
        { // 처음 시작하고 싶은 숫자
            fgets(buf, MAX, stdin);
            num = stoi(buf); //우리가 입력한 숫자
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

        switch (cnt)
        {
        case 0:
            scanf("%d", &intanswer);
            if (intanswer == num)
            {
                printf("정답!\n");
                buf = itoa(num + 1);
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
                buf = itoa(num + 1);
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
                buf = itoa(num + 1);
            write(sock_flag, buf, sizeof(buf));
            break;
            else
            {
                printf("오답!\n");
                break;
            }
        case 3:
            scanf("%s", answer);
            if (strcmp(answer, "ccc") == 0)
                buf = itoa(num + 1);
            write(sock_flag, buf, sizeof(buf));
            break;
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
