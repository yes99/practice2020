#include <stdio.h>
#include <sys/socket.h> //socket
#include <netinet/in.h> //IPPROTO_TCP, sockaddr_in
#include <stdlib.h>     //implicit declaration of function exit
#include <string.h>     //memset()

#define MAX 128
#define SERVER_PORT 16648
#define PENDING 10

int DATA_SEND_RECV(int conn_flag)
{
    char buf[MAX];
    int idx;
    //while(true){...}
    int num;
    int first = 0;

    //while(true){...}
    while (1)
    {
        memset(buf, 0x00, MAX);
        read(conn_flag, buf, sizeof(buf));
        printf("From client: %s\nTo client: ", buf);
        printf("your turn now ");
        num = atoi(buf);

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
                write(conn_flag, buf, sizeof(buf));
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
                write(conn_flag, buf, sizeof(buf));
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
            write(conn_flag, buf, sizeof(buf));
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
            write(conn_flag, buf, sizeof(buf));
            break;
            else
            {
                printf("오답!\n");
                break;
            }
        }

        printf("\nlength of buff : %d\n", strlen(buf));
        if (strncmp("exit", buf, 4) == 0)
        {
            printf("서버 종료 ...\n");
            break;
        }
    }
}
