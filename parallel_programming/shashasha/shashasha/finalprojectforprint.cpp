#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sha1.h"
#include "hmac.h"

#ifndef byte
#define byte unsigned char
#endif

#define DIGIT 6
#define NUMERAL 36

const char* lookup = "0123456789abcdefghijklmnopqrstuvwxyz"; // 0 ~ zÀÇ 36Áø¼ö

char* arrToStr(int* arr, int size, char* str);
void addOne(int* arr);
void findkey(byte keyDigest[]);
void printHex(byte msg[], byte length);

int main()
{
    byte keyDigest[20];
    srand((unsigned int)time(NULL));
    char key[DIGIT + 1];
    printf("put %d digit password >>> ", DIGIT);
    scanf("%s", &key);
    sha1((const byte*)key, DIGIT, keyDigest);
    printf("Hashed Value : ");
    printHex(keyDigest, 20);
    printf("\n");

    clock_t st = clock();
    findkey(keyDigest);
    clock_t ed = clock();
    printf("Elapsed Time : %d ms\n", ed - st);
    free(keyDigest);
    return 0;
}

void addOne(int* arr)
{
    arr[0] += 1;
    for (int i = 0; i < DIGIT; ++i)
    {
        if (arr[i] == NUMERAL)
        {
            arr[i] = 0;
            if (i != DIGIT - 1)
                arr[i + 1] += 1;
        }
        else
        {
            return;
        }
    }
}

void findkey(byte keyDigest[])
{

    printf("Notice : Finding the KEY ...\n");
    int find[DIGIT];
    for (int i = 0; i < DIGIT; i++)
        find[i] = 0;
    char* findstr = (char*)malloc(sizeof(char) * (DIGIT + 1));
    byte findDigest[20];
    int isSame = 0;
    while (1)
    {
        addOne(find);
        findstr = arrToStr(find, DIGIT, findstr);
        sha1((const byte*)findstr, DIGIT, findDigest);

        for (int i = 0; i < 20; i++)
        {
            if (keyDigest[i] == findDigest[i])
            {
                isSame++;
            }
        }
        if (isSame == 20)
        {
            printf("Notice : Key Found!!\n");
            printf("Found KEY >>> %s\n", findstr);
            free(findstr);

            return;
        }
        else
        {
            isSame = 0;
            continue;
        }
    }
    printf("Notice : Search Failed.\n");
    free(findstr);
}

char* arrToStr(int* arr, int size, char* str)
{
    for (int i = size - 1; i >= 0; --i)
    {
        str[size - i - 1] = lookup[arr[i]];
    }
    str[size] = NULL;
    return str;
}

void printHex(byte msg[], byte length)
{
    printf("0x");
    for (byte i = 0; i < length; i++)
    {
        if (msg[i] > 0x0f)
        {
            printf("%x", msg[i]);
        }
        else
        {
            printf("0%x", msg[i]);
        }
    }
    printf("\n");
}