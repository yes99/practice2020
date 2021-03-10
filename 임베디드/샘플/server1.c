#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#define PORT 5000
#define MAXPENDING 5
#define BUFSIZE 1024

int main(int argc, char *argv[])
{
    int sockfd, servsockfd;
    struct sockaddr_in serv_addr;
    int servlen,recvlen;
    char recvbuff[1024];
    time_t ticks;
    size_t fpsize=0, fsize=0;

    /*파일관련 함수*/
    char buff[1024];
    char path[]="/root/kimsh5130/data/";
    FILE *fp = NULL;

        //소켓 함수 설정
        if((sockfd=socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            perror("socket failed\n");
            close(1);
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(PORT);

        if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
            perror("bind failed\n");
            close(1);
        }

        if(listen(sockfd,MAXPENDING) == -1 ){
            perror("listen failed\n");
            close(1);
        }

        servlen = sizeof(serv_addr);
        if((servsockfd=accept(sockfd, (struct sockaddr*)&serv_addr, &servlen)) == -1) {
            perror("accept failed\n");
            close(1);
        }

        /*로컬 소켓의 정보를 얻어온다*/
            getpeername(servsockfd, (struct sockaddr *)&serv_addr, &servlen);
            printf("[클라이언트 접속] IP: %s , Port: %d\n",inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));
    while(1)
    {
        if((recvlen=recv(servsockfd, recvbuff, BUFSIZE-1, 0)) == -1) {
            perror("recv failed\n");
            break;
        }
        /*전송 데이터가 존재할 경우*/
        if(recvlen > 0)
        {
            recvbuff[recvlen] = 0x00;
            /*전송 받은 데이터가 문자 D 인 경우*/
            if(strlen(recvbuff)== 2  && !strncmp(recvbuff,"d",1))
            {
                /*파일명 수신 대기*/
                if((recvlen=recv(servsockfd, recvbuff, BUFSIZE-1, 0)) == -1){
                    perror("recv failed\n");
                    break;
                }
                //strncat(path, recvbuff,1);      /*경로명 + 파일명*/
                strcpy(path+21, recvbuff);
                path[strlen(path)-1]=0x00;
                printf("파일 경로 : %s\n",  path);
                fp=fopen(path, "r");

                if(fp == NULL)
                {
                    perror("파일이 존재하지 않습니다.\n");
                    break;
                }

                   while(( fpsize=fread(buff,1,BUFSIZE-1,fp))>0){
                        send(servsockfd,buff,BUFSIZE-1,1);
                }

                printf("파일 전송이 완료 되었습니다.\n");
                strcpy(buff, "f");
                sleep(5);
                fclose(fp);
                break;
            }
            if(strncmp(recvbuff, "quit",4)==0)
            {
                printf("클라이언트의 요청으로 인한 종료");
                break;
            }

            printf(" [알림] : %s\n", recvbuff);
            if(send(servsockfd, recvbuff, strlen(recvbuff),0) == -1){
                perror("send failed\n");
                 break;
            }

        }

    }
        close(sockfd);
    close(servsockfd);
    sleep(1);
    sleep(1);
}