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
int 369(int);
int headtail(int);


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


int 369(int sock_flag)
{
    char buf[MAX];
    int idx;
    int a, b, c; //각 1 10 100의자리수
    int ianswer;
    //while(true){...}
    int num;
    int first = 0;
    int cnt; //박수칠 횟수
    int check;
    char *answer = (char *)malloc(sizeof(char) * 10);
    char *num_string = (char *)malloc(sizeof(char) * 10);
    char temp[100];
    while (1)
    {
        //
        cnt = 0;
        printf("입력하세요: ");
        check = 0 ;   // 1은 정답 0은 오답

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
        while (1)
        {
            switch (cnt)
            {
            case 0:
                scanf("%d", &ianswer);
                if (ianswer == num)
                {
                    printf("정답!\n");
                    sprintf(buf, "%d", num + 1);
                    //strcpy(buf, itoa(num + 1, temp, 10));
                    write(sock_flag, buf, sizeof(buf));
                    check = 1;
                    break;
                }
                else
                {
                    printf("오답!\n");
                    check = 0;
                    break;
                }
            case 1:
                scanf("%s", answer);
                if (strcmp(answer, "c") == 0)
                {
                    printf("정답!\n");
                    sprintf(buf, "%d", num + 1);
                    // strcpy(buf, itoa(num + 1, temp, 10));
                    write(sock_flag, buf, sizeof(buf));
                    check = 1;
                    break;
                }
                else
                {
                    printf("오답!\n");
                    check = 0;
                    break;
                }
            case 2:
                scanf("%s", answer);
                if (strcmp(answer, "cc") == 0)
                {
                    printf("정답!\n");
                    sprintf(buf, "%d", num + 1);
                    //strcpy(buf, itoa(num + 1, temp, 10));
                    write(sock_flag, buf, sizeof(buf));
                    check = 1;
                    break;
                }
                else
                {
                    printf("오답!\n");
                    check = 0;
                    break;
                }
            case 3:
                scanf("%s", answer);
                if (strcmp(answer, "ccc") == 0)
                {
                    printf("정답!\n");
                    sprintf(buf, "%d", num + 1);
                    //strcpy(buf, itoa(num + 1, temp, 10));
                    write(sock_flag, buf, sizeof(buf));
                    check = 1;
                    break;
                }
                else
                {
                    printf("오답!\n");
                    check = 0;
                    break;
                }
            }
            printf("스위치문 탈출, if분기접 시작 \n");
            if(check ==1)
            {
                break;
            }         
            else if(check ==0)
            {
                printf("정답을 다시 입력하세요: ");
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

int headtail(int sock_flag)
{
    char buf[MAX];
    char buf2[MAX];
    int life = 4;
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
                    life--;
                }
                if (life == 0)
                {
                    printf("you lose\n");
                    break;
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