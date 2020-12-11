#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char message[256] = "fwefwefweafwaef|aewfawfwefewf|iuoiuiouiou";
    char flag[15];
    char stid[12];
    char data[200];
    char temp[200];
    int msgcnt = 0;
    char* s[3];

    s[0] = strtok(message, "|");
    s[1] =  strtok(NULL, "|");
    s[2] = strtok(NULL, "|");
    strcpy(data , s[2]);



    //strcpy(stid, argv[0]);
    //printf("1.  %s", flag);
    //            printf("\n");

    //printf("2.   %s", stid);
    //            printf("\n");

    printf("3.   %s", data);

}
