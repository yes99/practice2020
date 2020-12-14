#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#define MAX 128
#define PORT 16648
#define PENDING 10
#define CLIENT_SIZE 5

int tsn(int);

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
    char menu[2];
    char rmenu;
    char buf[MAX];
    int check;
    while(1)
    {
        printf("메뉴\n1.채팅\n2.369\n3.끝말잇기\n4.숫자야구\n5.행맨6.프로그램 끝내기");
        check = read(conn_flag, menu, sizeof(buf));
        printf("debug check : %d\n" , check);
        printf("debug menu: %s\n", menu);
        rmenu= menu[0];
        printf("rmenu %c", rmenu);
        if(rmenu == '1')
        {
            //DATA_SEND_RECV(conn_flag); // 채팅
        }
        else if(rmenu == '2')
        {
            tsn(conn_flag);//369
        }
        else if(menu == '3')
        {
            //끝말잇기            
        }
        else if(menu == '4')
        {
            //숫자야구
        }
        else if(menu == '5')
        {
            //행맨
        }
        else if (menu == '6')
        {
            break; // 프로그램 완전 끝내기
        }
    }
    close(sock_flag);
}

int tsn(int conn_flag)
{
    char buf[MAX];
    int idx;
    //while(true){...}
    int a, b, c; //각 1 10 100의자리수
    int ianswer;
    int num;
    int first = 0;
    int check;
    int cnt; //박수칠 횟수
    char *answer = (char *)malloc(sizeof(char) * 10);
    char *num_string = (char *)malloc(sizeof(char) * 10);
    char temp[100];
    int life = 2;
    //while(true){...}
    printf("GAME START\n");
    while (1)
    {
        cnt = 0;
        check = 0 ;   // 1은 정답 0은 오답
        memset(buf, 0x00, MAX);
        read(conn_flag, buf, sizeof(buf));
        if (strncmp("##", buf, 4) == 0)
        {
            printf("서버 종료 ...\n");
            break;
        }
        printf("From client: %s\n", buf);
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
        printf("1차 연산 완료 cnt = %d\n", cnt);
        while (1)
        {
            switch (cnt)
            {
            case 0:
                scanf("%d", ianswer);
                if (ianswer == num)
                {
                    printf("정답!\n");
                    sprintf(buf, "%d", num + 1);
                    //strcpy(buf, itoa(num + 1, temp, 10));
                    write(conn_flag, buf, sizeof(buf));
                    check = 1;
                    break;
                }
                else
                {
                    printf("오답! \n again :");
                    check = 0;
                    break;
                }
            case 1:
                scanf("%s", answer);
                if (strcmp(answer, "c") == 0)
                {
                   printf("정답!\n"); 
                    sprintf(buf, "%d", num + 1);
                    //strcpy(buf, itoa(num + 1, temp, 10));
                    write(conn_flag, buf, sizeof(buf));
                    check = 1;
                    break;
                }
                else
                {
                    printf("오답! \n again :");
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
                    write(conn_flag, buf, sizeof(buf));
                    check = 1;
                    break;
                }
                else
                {
                    printf("오답! \n again :");
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
                    write(conn_flag, buf, sizeof(buf));
                    check = 1;
                    break;
                }
                else
                {
                    printf("오답! \n again :");
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
                life--;
                printf("life left : %d\n", life);
                printf("정답을 다시 입력하세요 ");
            }
            if(life<0)
            {
                write(conn_flag, "##", sizeof(buf));
                return 0;
            }

        }
        //printf("\nlength of buff : %d\n", strlen(buf));
        /*if (strncmp("exit", buf, 4) == 0)
        {
            printf("서버 종료 ...\n");
            break;
        }*/
    }
}

