#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define DIGIT 6
char str[17] = "0123456789ABCDEF";


// 단지 현재 문자열이 뭔지 출력하는 함수.
void Show(char* data)
{
    for (int i = 0; i < DIGIT; i++)
        printf("%c", data[i]);
    printf("\n");
}

// 처음에 난수 문자열을 만드는 함수.
// 여기서 생긴 문자열을 해시 함수에 입력하여 해시값을 만든다.
char* MakePW()
{
    char* pw = (char*)malloc(sizeof(char) * DIGIT);
    for (int i = 0; i < DIGIT; i++)
        pw[i] = str[rand() % 16];
    return pw;
}



// 해시값을 토대로 원래 문자열을 찾는 함수의 메인.
// 인자는 다음과 같이 받아야 한다. 1. 해시 테이블, 2. 해시값의 개수
// 지금은 임시로 pwString이라는 인자를 받았는데 이건 수정해야함.
// 일단 그건 놔둬보셈.
void decoding(char* pwString)
{
    int i = 0;
    char* inputString = (char*)malloc(sizeof(char) * DIGIT);
    for (i = 0; i < DIGIT; i++)
        inputString[i] = str[0];
    // inputString의 초깃값을 000000으로 초기화
    int sameCount = 0;
    clock_t st = clock();
    while (1)
    {
        /////////////////////////////////////////////////////////////

        // 이 부분에 inputString을 1씩 올리는 부분을 추가해야 함.
        // 첨부한 다른 소스파일에 그 함수가 있는데 여기로 옮겨야할듯
        // 그냥 째로 갖다붙이면 안되고 적절하게 변환시켜 옮겨야할듯

        //////////////////////////////////////////////////////////////

        // 생성한 inputString과 해시테이블의 값을 비교하는 부분.
        // 모든 해시테이블과 값이 다르면 break하여 다시 루프를 돈다.
        // 일치하는 해시값이 있으면 출력 후 임시배열에 저장한다.
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
    printf("시작하려면 아무 키를 입력하세요.\n");
    scanf("%d", &zz);
    decoding(pwString);

    free(pwString);
    return 0;
}

