#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void token(char message[], char flag[], char stid[], char data[])
{
    printf("function start\n");
    char temp[200];
    int msgcnt = 0;
    //printf("%s\n", argv[0]);
    char* ptr = strtok(message, "|"); // 공백 문자를 기준으로 문자열을 자름, 포인터 반환
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
        printf("1.  %s", flag);
        printf("\n");
    }

    printf("1.  %s", flag);
    printf("\n");
    /*strcpy(stid, argv);
    printf("1.  %s", flag);
    printf("\n");

    printf("2.   %s", stid);
    printf("\n");

    printf("3.   %s", data);*/
}

int main(int argc, char* argv[])
{
    char message[256]= "abc|defwt|zzzzweuueu";
    char flag[15];
    char stid[12];
    char data[200];
    char temp[200];
    int msgcnt = 0;
    //scanf("%s", message);
    token(message, flag, stid, data);
    strcpy(stid, argv[0]);

    printf("1.  %s", flag);
    printf("\n");

    printf("2.   %s", stid);
    printf("\n");

    printf("3.   %s", data);
}
