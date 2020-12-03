#include <stdio.h>         // puts()
#include <string.h>        // strlen()
#include <fcntl.h>         // O_WRONLY
#include <unistd.h>        // write(), close()

#define  BUFF_SIZE  256     // 버퍼의 크기가 작습니다.

int main()
{
   char     buff[200];
   int      fd;
   ssize_t  rd_size;

   if (( fd = open( "a.txt", O_RDONLY)>0))
   {
      while(( rd_size = read( fd, buff, 199)>0))
      {  //  4 byte씩 읽씁니다.
        buff[rd_size]  = '\0';      // puts()를 위해 NULL을 대입
        //printf("FLAG_DOWNLOAD|2016112648|");
        puts( buff);
      }
      close( fd);
   } else {
      printf( "파일 열기에 실패했습니다.\n");
   }
   return 0;
}