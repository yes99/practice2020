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
    FILE *fp1, *fp2;
    
    if(0<(fd = creat("./result.txt", 0644)))
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

    fp2 = fopen("result.txt", "w");
    
    while ((c = fgetc(fp1)) != EOF)
        if(c>96 && c <123)
        {
            fputc(c-32, fp2);
        }
        else
        {
            fputc(c, fp2);
        }
    printf("변경된 문자를 새로운 파일 result.txt 라고 입력된 텍스트 파일에 복사된 값이 저장되었습니다.");
    fclose(fp1);
    fclose(fp2);
    return 0;
}
