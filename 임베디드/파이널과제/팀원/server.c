#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <time.h>

#define MAX 128
#define PORT 16648
#define PENDING 10
#define CLIENT_SIZE 5

int DATA_SEND_RECV(int);

int BaseBall(int);

int Hangman(int);

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

    //DATA_SEND_RECV(conn_flag);
    //BaseBall(conn_flag);
    Hangman(conn_flag);

    close(sock_flag);
}

int DATA_SEND_RECV(int conn_flag)
{
    char buf[MAX];
    char buf2[MAX];

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
            }
        }

        if (strncmp("exit", buf, 4) == 0)
        {
            printf("서버 종료 ...\n");
            break;
        }
    }
}

int BaseBall(int conn_flag)
{
    int computerBall[3]; // 컴퓨터의 볼을 저장할 int형 배열
    int i, j; // 반복을 위한 변수
    int temp; // 난수 중복 체크를 위한 변수
    int userBall[3]; // 사용자의 볼을 저장할 int형 배열
    int count = 1; // 회차를 확인할 변수 9회까지 가능
    int strike; // 스트라이크의 수를 세기 위한 변수
    int ball; // 볼의 수를 세기 위한 변수
    int endflag=0; //game finsh

    srand((unsigned)time(NULL));
    for (i = 0; i < 3; i++)
    {
        temp = (rand() % 9) + 1; // temp변수에 현재 랜덤 값을 저장
        computerBall[i] = temp; // temp값을 컴퓨터의 볼에 저장
        for (j = 0; j < i; j++) // 현재 추가된 만큼 반복하며
            if (temp == computerBall[j] && i != j) // 만약 현재 temp값과 이전에 넣은 값 중 동일한 게 있다면
                i--; // i의 값을 줄여 다시 이전으로 돌아가도록
    }

    char buf[MAX];//get
    char buf2[MAX];//sending
    int buf1 =0;
    memset(buf2, 0x00, MAX);
    memset(buf, 0x00, MAX);

    while(1)
    {

        sprintf(buf2,"[%d회차 숫자야구]\n", count);
        write(conn_flag, buf2, sizeof(buf2));


        read(conn_flag, buf, sizeof(buf));

        buf1 = atoi(buf);
        userBall[0]=buf1/100;
        userBall[1]=(buf1%100)/10;
        userBall[2]=buf1%10;

        ball = 0;
        strike = 0;

        for (i = 0; i < 3; i++) // computerBall 1~3번째에 따라 각 userBall 1~3번째를 확인하기 위한 반복
            for (j = 0; j < 3; j++)
                if (computerBall[i] == userBall[j]) // computerBall과 userBall의 값이 같다면
                    if (i == j) // 같은 위치일 경우
                        strike++; // 스트라이크 개수 증가
                    else // 다른 위치일 경우
                        ball++; // 볼 개수 증가

        // 확인한 결과를 출력

        if (strike == 3) // 만약 스트라이크 개수가 3개이면 승리
        {
            endflag=1;
            sprintf(buf2,"***** 승리했습니다. *****\n\n");
            write(conn_flag, buf2, sizeof(buf2));

            sprintf(buf2,"%d",endflag);
            write(conn_flag, buf2,sizeof (buf2));
            break;
        }
        else if (count == 9) // 만약 9회차인데도 승리하지 못하면 패배
        {
            endflag=1;
            sprintf(buf2,"***** 패배했습니다.. 정답 : %d %d %d *****\n\n", computerBall[0], computerBall[1], computerBall[2]);
            write(conn_flag, buf2, sizeof(buf2));

            sprintf(buf2,"%d",endflag);
            write(conn_flag, buf2,sizeof (buf2));
            break;
        }
        sprintf(buf2,"[결과]스트라이크 : %d, 볼 : %d\n\n", strike, ball);
        write(conn_flag, buf2, sizeof(buf2));

        sprintf(buf2,"%d",endflag);
        write(conn_flag, buf2,sizeof (buf2));
        count++;
    }

}

int Hangman(int conn_flag)
{
    char ch;
    int cnt = 0;
    //  등록된 단어 사전​
    const char *dic[] = {"boy","good","student", "university", "chair", "desk", "computer", "mask", "holiday" };
    int wnum = sizeof(dic) / sizeof(char *);  // 등록된 단어의 개수
    int i;
    int sel;
    const char *word;
    char *pword;
    int len;

    int endflag=0; //game finsh


    char buf[MAX];
    char buf2[MAX];

    memset(buf2, 0x00, MAX);
    memset(buf, 0x00, MAX);

    srand(time(NULL));     // 난수 시드 조정
    sel = rand() % wnum;   // 임의의 단어 첨자
    word = dic[sel];          // 임의의 단어 포인터

    len = strlen(word);       // 단어의 길이
    pword = (char *)malloc(len + 1);   // 화면에 나타나는 단어 배열

    for (i = 0; i < len; i++)
        pword[i] = '_';     //  화면에 나타나는 단어 _ 로 초기화
    pword[len] = '\0';

    sprintf(buf2,"== 단어 맞추기 게임 ==\n");
    write(conn_flag, buf2, sizeof(buf2));

    while(1)
    {
        sprintf(buf2,"\n맞출단어 : %s",pword);
        write(conn_flag, buf2, sizeof(buf2));

        read(conn_flag,buf,sizeof(buf));
        ch = buf[0];
        cnt++;

        for (i = 0; i < len; i++)
            if (pword[i] == '_' && word[i] == ch)   // 입력된 문자가 아직 가려져 있으면
                pword[i] = ch;                          // 화면에 그 문자를 나타냄

        for (i = 0; i < len; i++)
            if (pword[i] == '_') break;       //  가려져 있는 문자가 있는가?


        if(i==len){
            endflag=1;
        }
        sprintf(buf2,"%d",endflag);
        write(conn_flag, buf2,sizeof (buf2));

        if (i == len) {    // 가려진 문자가 없으면, 즉 다 맞추었으면
            sprintf(buf2,"\n%d 번만에 %s를 맞추었습니다.\n\n", cnt, pword);
            write(conn_flag, buf2, sizeof(buf2));
            break;
        }

    }
}
