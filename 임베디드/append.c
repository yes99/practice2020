#include <stdio.h>         // puts()
#include <string.h>        // strlen()
#include <fcntl.h>         // O_WRONLY
#include <unistd.h>        // write(), close()
#include <time.h>
#include <stdlib.h>

/* 파일 복사 프로그램 */
int main(int argc, char *argv[])
{
    char c;
    int fd;
    FILE *fp1, *fp2, *fp3;
    
    if(0<(fd = creat("./append_result.txt", 0644)))
    {

    }
    else
    {
        printf("wrong command");
    }
    
    
    fp1 = fopen(argv[1], "r");
    if (fp1 == NULL)
    {
        fprintf(stderr, "파일 %s 열기 오류\n", argv[1]);
        return 2;
    }

    fp2 = fopen("append_result.txt", "w");
    while ((c = fgetc(fp1)) != EOF)
    {
        fputc(c, fp2);
    }
        
    fclose(fp1);
    fclose(fp2);

    fp1 = fopen(argv[2], "r");
    if (fp1 == NULL)
    {
        fprintf(stderr, "파일 %s 열기 오류\n", argv[1]);
        return 2;
    }

    fp2 = fopen("append_result.txt", "a");
    while ((c = fgetc(fp1)) != EOF)
        fputc(c, fp2);


    fclose(fp1);
    fclose(fp2);

    return 0;
}