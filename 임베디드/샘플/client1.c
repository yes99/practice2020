#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 5000
#define BUFFER 1024

/*argv[1] IP 주소*/
int main(int argc, char *argv[])
{
  int sockfd = 0, n = 0;
  int recvlen;
  char sendbuff[BUFFER];
  char recvbuff[BUFFER];
  char buffer[BUFFER];
  char path[]="/root/kimsh5130/file/";
  struct sockaddr_in serv_addr;
  char filename[100];
  FILE *fp=NULL;
  char tmp[128];

  if(argc != 2)
  {
      printf("Usage: %s <ip of server> \n",argv[0]);
      close(1);
  }

  if((sockfd=socket(AF_INET, SOCK_STREAM, 0)) == -1) {

      perror("socket failed\n");
      close(1);
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) == -1)
  {
      printf("inet_pton error\n");
      close(1);
  }

  if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
  {
      perror("connect failed\n");
      close(1);
  }
while(1)
{
     printf("Send Message : ");
     fgets(buffer, BUFFER,stdin);
     /*quit 입력시 종료*/
     send(sockfd, buffer, strlen(buffer),0);
     sleep(1);
     if(strncmp(buffer, "quit",4)==0)
     {
          break;

     }

     else if(!strncmp(buffer,"d",1) && strlen(buffer)==2)
     {
        printf("다운받을 파일명 :");
        scanf("%s", filename);
        send(sockfd, filename, strlen(filename),0);

        strcpy(path+21, filename);
        printf("%s\n", path);
        fp=fopen(path, "w");

        while((recvlen=recv(sockfd, recvbuff, BUFFER-1, 0)) > 0){
            recvbuff[recvlen]=0x00;
           // if(recvbuff[0] =='f' && recvlen == 1)
           //     break;
            fwrite(recvbuff, 1,recvlen,fp);
        }
        printf("다운로드가 완료되었습니다.\n");
        fclose(fp);
        break;
    }
    else if((recvlen=recv(sockfd, recvbuff, BUFFER-1, 0)) == -1)  {
          perror("recv failed\n");
          break;
    }
    recvbuff[recvlen] = '\0';
    printf("[알림] : %s\n", recvbuff);
}
  close(sockfd);
  return 0;
}
