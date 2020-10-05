#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>

int main()
{
    double input;
    double number;
    char binary[60] = { 0, };
    int i, j, k;
    int cnt = 0;
    int key;
    printf("Single Precision FP value:");
    scanf("%lf", &input);
    int origin;
    ;// S만들기======================================
    if (input >= 0)
    {
        number = input;
    }
    else
    {
        number = -1 * input;
    }
    //====================F 만들기 시작 0초과는 다 되는듯
    char tempA[50];
    int tempi = number;
    origin = tempi;
    i = 0;
    if (tempi > 0)
    {
        while (1)
        {
            if (tempi % 2 == 1)
            {
                tempA[i] = 1;
            }
            else
            {
                tempA[i] = 0;
            }
            tempi = tempi / 2;
            i++;
            cnt++;
            if (tempi == 0)
            {
                break;
            }
        }

        for (i = 0; i < cnt; i++)
        {
            binary[i] = tempA[cnt - 1 - i];
        }
        binary[cnt] = '.';
        key = cnt;
        //printf("정수 파트만 : ");
        //for (i = 0; i < key + 1; i++)
        //{
        //    printf("%d", (binary[i]));
        //}
        //printf("\n\n");
        //printf("key = %d", key);
        //printf("\n\n");
    }
    else
    {
        binary[0] = 0;
        binary[1] = '.';
        key = 1;
        //////////////
        //printf("정수 파트만 : ");
        //for (i = 0; i < key + 1; i++)
        //{
        //    printf("%d", (binary[i]));
        //}
        //printf("\n\n");
        //printf("key = %d", key);
        //printf("\n\n");

    }

    double tempf = number - origin;
    cnt = 0;
    char tempB[50] = { 0, };
    i = 0;
    while (1)
    {
        if (tempf * 2 >= 1)
        {

            tempB[i] = 1;
            tempf = tempf * 2 - 1;
        }
        else
        {
            tempB[i] = 0;
            tempf = tempf * 2;
        }
        i++;
        cnt++;
        if (tempf == 0)
        {
            break;
        }
        if (i == 49)
        {
            break;
        }
    }
    /* printf("tempB 임시저장 즉 소수점만:  ");

     for (i = 0; i < cnt; i++)
     {
     printf("%d", tempB[i]);
     }*/
    printf("\n"); // 여기까지는 문제가 없는 듯 하다
    for (i = key + 1; i < key + cnt + 1; i++)
    {
        binary[i] = tempB[i - 1 - key];
    }

    printf("바이너리 출력:  ");
    for (i = 0; i < 23; i++)
    {
        if (binary[i] != 46)
        {
            printf("%d", binary[i]);
        }
        else if (binary[i] == 46)
        {
            printf(".");
        }
    }
    printf("\n");
    int key2;
    if (binary[0] == 1)
    {
        for (i = 0; i < 23; i++)
        {
            if (binary[i] == 46)
            {
                key2 = i;
                break;
            }
        }
        for (i = key - 1; i > 0; i--)
        {
            binary[i + 1] = binary[i];
        }
    }
    else if (binary[0] == 0)
    {
        for (i = 0; i < 23; i++)
        {
            if (binary[i] == 1)
            {
                key2 = i;
                break;
            }
        }
        binary[0] = binary[key2];
        for (i = 0; i < 23; i++)
        {
            binary[i + 2] = binary[key2 + 1 + i];
            // printf("\%d", (binary[i]));
        }
    }
    binary[1] = 88;
    printf("\n");
    if (input >= 0)
    {
        printf("S: 0");
    }
    else
    {
        printf("S: 1");
    }
    /* printf("일단 바이너리 ");
     for (i = 0; i < 23; i++)
     {
         printf("\%d", (binary[i]));
     }*/
    printf("\n");
    printf("F: ");
    for (i = 2; i < 25; i++)
    {
        printf("%d", (binary[i]));
    }
    printf("\n");
    //=========------E만들기
    int Eready;
    //= key - 1
    if (input >= 1)
    {
        Eready = key - 1;
    }
    else
    {
        Eready = (key2 - 1) * (-1);
    }

    int E = Eready + 127;
    int Earray[8] = { 0, };
    int finalEarray[8];
    i = 0;
    while (1)
    {
        if (E % 2 == 1)
        {
            Earray[i] = 1;
        }
        else
        {
            Earray[i] = 0;
        }
        E = E / 2;
        i++;
        cnt++;
        if (E == 0)
        {
            break;
        }
    }
    for (i = 0; i < 8; i++)
    {
        finalEarray[i] = Earray[7 - i];
    }
    printf("E: ");
    for (i = 0; i < 8; i++)
    {
        printf("%d", (finalEarray[i]));
    }
    // E 만들기 완료!

    //전체 FP 출력
    printf("\n");
    printf("전체 바이너리 출력:");
    if (input >= 0)
    {
        printf("0");
    }
    else
    {
        printf("1");
    }
    for (i = 0; i < 8; i++)
    {
        printf("%d", (finalEarray[i]));
    }
    for (i = 2; i < 25; i++)
    {
        printf("%d", (binary[i]));
    }
    //완료

    return 0;
}