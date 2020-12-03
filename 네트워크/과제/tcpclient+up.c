#include <stdio.h>
#include <sys/socket.h> //socket
#include <netinet/in.h> //IPPROTO_TCP, sockaddr_in
#include <stdlib.h>     //implicit declaration of function exit
#include <string.h>     //memset()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 128
#define SERVER_PORT 45000
#define PENDING 10

int DATA_SEND_RECV(int sock_flag, char stid[]);
void tokenuserfile(char data[])
{
    //printf("function start\n");
    char temp[200];
    //printf("%s\n", argv[0]);
    char *ptr = strtok(data, "\n"); // 공백 문자를 기준으로 문자열을 자름, 포인터 반환
    printf("%s\n", ptr);
    while (ptr != NULL) // 자른 문자열이 나오지 않을 때까지 반복
    {
        // 자른 문자열 출력
        ptr = strtok(NULL, "\n"); // 다음 문자열을 잘라서 포인터를 반환        {
        printf("%s\n", ptr);
    }
}
void token(char message[], char flag[], char stid[], char data[])
{
    printf("function start\n");
    char temp[200];
    int msgcnt = 0;
    //printf("%s\n", argv[0]);
    char *ptr = strtok(message, "|"); // 공백 문자를 기준으로 문자열을 자름, 포인터 반환
    strcpy(flag, ptr);
    // printf("1.  %s", flag);
    //printf("\n");

    while (ptr != NULL) // 자른 문자열이 나오지 않을 때까지 반복
    {
        // 자른 문자열 출력
        ptr = strtok(NULL, "|"); // 다음 문자열을 잘라서 포인터를 반환
        if (msgcnt == 0)
        {
            strcpy(temp, ptr);
            //printf("2.   %s", temp);
        }
        else if (msgcnt == 1)
        {
            strcpy(data, ptr);
            // printf("3.   %s", data);
        }
        msgcnt++;
        //    printf("\n");
    }
}

int main(int argc, char *argv[])
{
    char message[256], stid[12];
    int sock_flag, conn_flag;
    struct sockaddr_in server_addr;
    strcpy(stid, argv[0]);
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
    server_addr.sin_addr.s_addr = inet_addr("210.94.172.185");
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

    DATA_SEND_RECV(sock_flag, stid);

    close(sock_flag);
}

int DATA_SEND_RECV(int sock_flag, char stid[])
{
    char buf[MAX];
    int idx;
    char flag[15];
    char data[200];
    char temp[200];

    //while(true){...}
    while (1)
    {

        int num;

        printf("메뉴입니다.\n");
        printf("1.flag_chat\n2.flag_upload\n3.flag_download\n4.flag_list_user\n5.flag_list_files\n6.flag_exit\n");
        printf("원하는 플래그를 선택하십시오");
        scanf("%d", &num);
        if (num == 1)
        {
            printf("flag chat을 사용합니다 ");
            memset(buf, 0x00, MAX);
            strcpy(buf, "FLAG_CHAT|");
            strcat(buf, stid);
            strcat(buf, "|Hello World\n");
            printf("전송한 문자는 %s\n", buf);
            write(sock_flag, buf, sizeof(buf));
            memset(buf, 0x00, MAX);
            read(sock_flag, buf, sizeof(buf));
            printf("From server: %s\n", buf);
            token(buf, flag, stid, data);
            printf("%s\n", data);
        }
        else if (num == 2)
        {
            char file[50];
            char buff[200];
            int fd;
            ssize_t rd_size;
            printf("flag upload를 사용합니다: ");
            printf("업로드 할 파일은?");
            scanf("%s", file);
            if ((fd = open(file, O_RDONLY)) > 0)
            {
                while ((rd_size = read(fd, buff, 200 - 1)) > 0)
                {                         //  4 byte씩 읽씁니다.
                    buff[rd_size] = '\0'; // puts()를 위해 NULL을 대입
                    memset(buf, 0x00, MAX);
                    strcpy(buf, "FLAG_UPLOAD|");
                    strcat(buf, stid);
                    strcat(buf, "|");
                    strcat(buf, buff);
                    printf("전송한 문자는 %s\n", buf);
                    write(sock_flag, buf, sizeof(buf));
                }
                memset(buf, 0x00, MAX);
                strcpy(buf, "FLAG_UPLOAD|");
                strcat(buf, stid);
                strcat(buf, "|");
                strcat(buf, "EOF");
                write(sock_flag, buf, sizeof(buf));
                memset(buf, 0x00, MAX);
                read(sock_flag, buf, sizeof(buf));
                printf("From server: %s\n", buf);
                close(fd);
            }
            else
            {
                printf("파일 열기에 실패했습니다.\n");
            }
        }
        else if (num == 3) //무엇을 더 해야하는가?
        {
            char file[200];
            printf("flag upload를 사용합니다: ");
            printf("다운로드 할 파일은?");
            scanf("%s", file);
            printf("flag download를 사용합니다");
            memset(buf, 0x00, MAX);
            strcpy(buf, "FLAG_DOWNLOAD|");
            strcat(buf, stid);
            strcat(buf, "|");
            strcat(buf, file);
            printf("전송한 문자는 %s\n", buf);
            write(sock_flag, buf, sizeof(buf));
            memset(buf, 0x00, MAX);
            read(sock_flag, buf, sizeof(buf));
            printf("From server: %s\n", buf);
        }
        else if (num == 4)
        {
            printf("flag list user을 사용합니다");

            memset(buf, 0x00, MAX);
            strcpy(buf, "FLAG_LIST_USER|");
            strcat(buf, stid);
            strcat(buf, "|NULL");
            printf("전송한 문자는 %s\n", buf);
            write(sock_flag, buf, sizeof(buf));
            memset(buf, 0x00, MAX);
            read(sock_flag, buf, sizeof(buf));
            printf("From server: %s\n", buf);
        }
        else if (num == 5)
        {
            printf("flag list file을 사용합니다.");

            memset(buf, 0x00, MAX);
            strcpy(buf, "FLAG_LIST_FILE|");
            strcat(buf, stid);
            strcat(buf, "|NULL");
            printf("전송한 문자는 %s\n", buf);
            write(sock_flag, buf, sizeof(buf));
            memset(buf, 0x00, MAX);
            read(sock_flag, buf, sizeof(buf));
            printf("From server: %s\n", buf);
        }
        else if (num == 6)
        {
            printf("flag exit을 사용합니다 ");
            memset(buf, 0x00, MAX);
            strcpy(buf, "FLAG_EXIT|");
            strcat(buf, stid);
            strcat(buf, "|NULL\n");
            printf("전송한 문자는 %s\n", buf);
            write(sock_flag, buf, sizeof(buf));
            memset(buf, 0x00, MAX);
            read(sock_flag, buf, sizeof(buf));
            printf("From server: %s\n", buf);
            break;
        }
        else
        {
            printf("wrong number");
        }
    }
}
