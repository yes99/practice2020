#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define DIGIT 4

char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
char integer[11] = "0123456789";


void Show(char* data)
{
   for (int i = 0; i < DIGIT; i++)
      printf("%c", data[i]);
   printf("\n");
}

char* MakePW()
{
   int isAlphabet;
   char* pw = (char*)malloc(sizeof(char) * DIGIT);
   
   for (int i = 0; i < DIGIT; i++)
   {
      isAlphabet = rand() % 2;
      if (isAlphabet == 1)
         pw[i] = alphabet[rand() % 26];
      else
         pw[i] = integer[rand() % 10];
   }
   return pw;
}

char* MakeInput(char* inputString)
{
   int isAlphabet;
   for (int i = 0; i < DIGIT; i++)
   {
      isAlphabet = rand() % 2;
      if (isAlphabet == 1)
         inputString[i] = alphabet[rand() % 26];
      else
         inputString[i] = integer[rand() % 10];
   }
   return inputString;
}

void decoding(char* pwString)
{
   char* inputString = (char*)malloc(sizeof(char) * DIGIT);
   int sameCount = 0;
   clock_t st = clock();
   while (1)
   {
      inputString = MakeInput(inputString);
      for (int i = 0; i < DIGIT; i++)
      {
         if (pwString[i] == inputString[i])
         {
            sameCount++;
            continue;
         }   
         else
         {
            //printf("암호 해독 실패...\n");
            sameCount = 0;
            break;
         }
      }
      if (sameCount == DIGIT)
      {
         printf("Notice : 암호 해독에 성공했습니다!!\n");
         printf("암호 >>> "); Show(inputString);
         free(inputString);
         break;
      }
   }
   clock_t ed = clock();
   printf("Notice : 걸린 시간 %dms\n", ed - st);   
}

int main(int argc, char* argv[])
{
   srand((unsigned int)time(NULL));
   int zz;
   char* pwString = MakePW();
   printf("생성된 암호>>> ");  Show(pwString);
   printf("해독을 시작하려면 1.\n");
   scanf("%d", &zz);
   decoding(pwString);
   
   free(pwString);
   return 0;
}