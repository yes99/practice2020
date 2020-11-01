#include <stdio.h>         // puts()
#include <string.h>        // strlen()
#include <fcntl.h>         // O_WRONLY
#include <unistd.h>        // write(), close()
#include <time.h>
#include <stdlib.h>

int main()
{
   int    fd;
   int i;
   int c;
   if ( 0 < ( fd = creat( "./text.txt", 0644)))  
   {
   }
   else 
   {
      printf( "파일 생성에 실패했습니다.n");
   }

    FILE *fp;
    fp = fopen("text.txt", "w");
    for(i = 0 ; i < 10000; i++)
    {
        c = rand() % 26 + 97;
        char letter = c;
        fputc(letter , fp);
    }

    fclose(fp);
  /* fd = open("text.txt", O_RDONLY);
   char find = lseek(fd , 100* sizeof(char), SEEK_SET);
   printf("%s", find);
   for ( i = 0 ; i < 99 ; i++)
   {
      char find = lseek(fd , 100* sizeof(char), SEEK_CUR);
      printf("%s", &find);
   }
*/
   return 0;
}