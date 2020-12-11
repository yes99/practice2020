#include <stdio.h>  // puts()
#include <string.h> // strlen()
#include <fcntl.h>  // O_WRONLY
#include <unistd.h> // write(), close()

#define BUFF_SIZE 256 // 버퍼의 크기가 작습니다.

int main()
{
   char buff[BUFF_SIZE];
   int fd;
   ssize_t rd_size;
   char file[50];
   printf("flag upload를 사용합니다: ");
   printf("업로드 할 파일은?");
   scanf("%s", file);
   if ((fd = open(file, O_RDONLY) > 0))
   {
      while ((rd_size = read(fd, buff, 200) > 0))
      {                        //  4 byte씩 읽씁니다.
         buff[rd_size] = '\0'; // puts()를 위해 NULL을 대입
                               //printf("%s|%s|%s", flag, stid, buff);
         memset(buf, 0x00, MAX);
         strcpy(buf, "FLAG_UPLOAD|");
         strcat(buf, stid);
         strcat(buf, buff);
         write(sock_flag, buf, sizeof(buf));
      }
      memset(buf, 0x00, MAX);
      strcpy(buf, "FLAG_UPLOAD|");
      strcat(buf, stid);
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
/*
   memset(buf, 0x00, MAX);
   strcpy(buf, "FLAG_UPLOAD|");
   strcat(buf, stid);
   strcat(buf, buff);
   write(sock_flag, buf, sizeof(buf));
   memset(buf, 0x00, MAX);
   read(sock_flag, buf, sizeof(buf));
   printf("From server: %s\n", buf);
*/
   return 0;
}
}