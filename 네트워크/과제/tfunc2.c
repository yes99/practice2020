#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tokenuser(char data[])
{
    //printf("function start\n");
    char temp[200];
    int msgcnt = 0;
    //printf("%s\n", argv[0]);
    char* ptr = strtok(data, "\n"); // 공백 문자를 기준으로 문자열을 자름, 포인터 반환
    printf("%s\n", ptr);
    while (ptr != NULL) // 자른 문자열이 나오지 않을 때까지 반복
    {
        // 자른 문자열 출력
        ptr = strtok(NULL, "\n"); // 다음 문자열을 잘라서 포인터를 반환
        if (msgcnt == 0)
        {
            printf("%s\n", ptr);
        }
    }
}

int main(int argc, char* argv[])
{
    char message[256]= "1.202012489\n2.fadsfjsdafklsdg\n3.fhWJFHwlgfhwgh\n4.awwagwegwegwg";
    token(message);
}
