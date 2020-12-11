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
    char file[50];
    char buff[200];
    int fd;
    int n;
    ssize_t rd_size;
    printf("flag download를 사용합니다: ");
    printf("다운로드 할 파일은?");
    scanf("%s", file);
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
    token(buf, flag, stid, data);
    if (data = "")
    {
    }
    else
    {
        if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
        {
            printf("파일 열기에 실패했습니다.\n");
            exit(0);
        }
        memset(buf, 0x00, MAX);
        while ((rd_size = read(fd, buff, 200 - 1)) > 0)
        {
            printf("테스트용 : buf = %s", buf);
            token(buf, flag, stid, data);
            printf("테스트용 : data = %s", data);
            if (data == "EOF")
            {
                break;
            }
            write(fd, data, n);
            memset(buf, 0x00, MAX);
        }
        close(fd);
    }
}

else if(idx == 2){ // download
         printf("Download File Name : ");
         scanf("%s", data);
         strcat(buf, data);

         write(sock_flag, buf, sizeof(buf));
         memset(buf, 0x00, MAX);
         read(sock_flag, buf, sizeof(buf));

         s[0] = strtok(buf, "|"); // flag
         s[1] = strtok(NULL, "|"); // user
         s[2] = strtok(NULL, "|"); // data
         strcpy(s_data, s[2]);

         if (strcmp(s_data, "[ERR] Not found file.") != 0)
         {
            if (0 > (fd = open(data, O_WRONLY | O_CREAT, 0644)))
            {
               printf("Failed to Open File...\n");
            }
            else
            {
               while (strcmp(s_data, "[DOWNLOAD] Done.") != 0)
               {
                  write(fd, s_data, strlen(s_data));
                  //printf("%s\n", s_data);
                  read(sock_flag, buf, sizeof(buf));
                  s[0] = strtok(buf, "|"); // flag
                  s[1] = strtok(NULL, "|"); // user
                  s[2] = strtok(NULL, "|"); // data
                  strcpy(s_data, s[2]);
                  //printf("%s\n", s_data);
               }
            }
            close(fd);
         }
      }

