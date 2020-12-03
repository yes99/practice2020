#include <stdio.h>         // puts()
#include <string.h>        // strlen()
#include <fcntl.h>         // O_WRONLY
#include <unistd.h>        // write(), close()

#define  BUFF_SIZE   200     // 버퍼의 크기가 작습니다.

int main()
{
   char     buff[200];
   int      fd;
   ssize_t  rd_size;

   if ( 0 < ( fd = open( "a.txt", O_RDONLY))){
      while( 0 < ( rd_size = read( fd, buff, 200-1))){  //  4 byte씩 읽씁니다.
         buff[rd_size]  = '\0';      // puts()를 위해 NULL을 대입
         printf("FLAG_DOWNLOAD|2016112648|");
         puts( buff);
      }
      close( fd);
   } else {
      printf( "파일 열기에 실패했습니다.\n");
   }
   return 0;
}