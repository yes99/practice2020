#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sha1.h"
#include "hmac.h"

#ifndef byte
#define byte unsigned char
#endif

#define DIGIT 4
#define NUMERAL 36

const char* lookup = "0123456789abcdefghijklmnopqrstuvwxyz"; // 0 ~ z의 36진수

char* arrToStr(int* arr, int size, char* str);
void addOne(int* arr);
void findkey(char* keyDigest);
void printHex(byte msg[], byte length);



int main()
{
    byte digest[20];
    srand((unsigned int)time(NULL));
    char key[DIGIT + 1];
    char* keyDigest = (char*)malloc(sizeof(char) * (DIGIT + 1)); // 해시 함수 적용하면 길이를 (40 + 1)으로 변경해야될듯.
    printf("put %d digit password >>> ",DIGIT);
    scanf("%s", &key);
    sha1((const byte*)key, DIGIT, digest);
    printf("Hashed Value : "); printHex(digest, 20); printf("\n");

    // key = sha(key.encode());
    // keyDigest = key.digest();

    clock_t st = clock();
    findkey(key);
    // findkey(keyDigest);
    clock_t ed = clock();
    printf("Elapsed Time : %d ms\n", ed - st);
    free(keyDigest);
    return 0;
}


void addOne(int* arr) {

    arr[0] += 1;
    for (int i = 0; i < DIGIT; ++i) {
        if (arr[i] == NUMERAL) {
            arr[i] = 0;
            if (i != DIGIT - 1)
                arr[i + 1] += 1;
        }
        else {
            return;
        }
    }
}

void findkey(char* keyDigest)
{
    printf("Notice : Finding the KEY ...\n");
    int find[DIGIT];
    for(int i = 0 ; i < DIGIT ; i++)
      find[i] = 0;
    char* findstr = (char*)malloc(sizeof(char) * (DIGIT + 1));
    char* findSha = (char*)malloc(sizeof(char) * (DIGIT + 1));
    char* findDigest = (char*)malloc(sizeof(char) * (DIGIT + 1));

    int isSame = 0;
    int cnt = 0;
    while (1)
    {
        addOne(find);
        findstr = arrToStr(find, DIGIT, findstr);

        // findSha = sha1();
        // findDigest = findSha.digest();


        for (int i = 0; i < DIGIT; i++)
        {
            if (keyDigest[i] == findstr[i]) // ==> if (keyDigest[i]== findDigest[i])
                isSame++;
        }

        if (isSame == DIGIT)
        {
            printf("Notice : Key Found!!\n");
            printf("Found KEY >>> %s\n",findstr); 
            free(findstr);
            free(findSha);
            free(findDigest);
            return;
        }
        else
        {
            //printf("KEY : "); Show(keyDigest);
            //printf("FIND : "); Show(findstr);
            cnt++;
            isSame = 0;
            continue;
        }
    }
    free(findstr);
    free(findSha);
    free(findDigest);
    printf("Notice : Search Failed.\n");
}

char* arrToStr(int* arr, int size, char* str) 
    {
    for (int i = size - 1; i >= 0; --i) {
        str[size-i-1] = lookup[arr[i]];
    }
    str[size] = NULL;
    return str;
}



void printHex(byte msg[], byte length) {
    printf("0x");
    for (byte i = 0; i < length; i++) {
        if (msg[i] > 0x0f) {
            printf("%x", msg[i]);
        }
        else {
            printf("0%x", msg[i]);
        }
    }
    printf("\n");
}
