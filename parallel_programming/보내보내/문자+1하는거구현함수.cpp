#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIGIT 6

// 실제 원본파일에 옮겨야 하는 함수는 BF_matching과 makeString이다.
// makeString은 이름이 좀 이상한가?? 적절한 이름 떠오르면 수정좀.
// 지금은 0~9인 경우에 작성한거라 0~f의 16진수로 바꿔야한다.
// 지금은 9가 진수의 마지막 문자이지만
// 16진수이면 f가 마지막 문자이겠지??

void Show(char* s)
{
    for (int i = 0; i < DIGIT; i++)
    {
        printf("%c", s[i]);
    }
    printf("\n");
}


// 옮겨야 하는 함수 1.
bool BF_matching(char* T, int n, char* P, int m)
{
    int i;
    for (i = 0; i < m; i++)
    {
        if (P[i] != T[n-m + i])
            return false;
    }
    if (i == m) // MATCH!
    {
        return true;
    }
}

// 옮겨야 하는 함수 2.
void makeString(char* T)
{
    T[0] = '9';
    T[1] = '9';
    T[2] = '9';
    T[3] = '1';
    T[4] = '9';
    T[5] = '8';
    printf("* 원래 T : "); Show(T);
    int m = DIGIT; // P의 자릿수.
    int d = 0;      
    while (1)
    {
        // 최종적으로 XXX999가 아닐 경우.
        // 문자열의 마지막 자리만 +1한다.
        if (m == 0)
        {
            printf("최종 실패.\n");
            T[DIGIT - 1]++;
            printf("* 1을 더한 후 : "); Show(T);
            return;
        }

        // T와 비교할 P를 생성.
        char* P = (char*)malloc(sizeof(char) * m);
        for (int i = 0; i < m; i++)
        {
            P[i] = '9';
        }
        
        // XXX999 인지 확인 및 inputString++ 을 하는 단계.
        bool right = BF_matching(T, DIGIT, P, m);
        // XXX999일 경우
        if (right == true)
        {   // 999999 일때 예외 처리.
            if (m == DIGIT)
            {
                printf("최대 숫자에 도달했습니다. 이 부분 수정하세요!!\n");
                return;
            }
            // ex) 199999 => 200000 으로 바꾸는 과정.
            else
            {
                T[d - 1]++;
            }
            for (int i = d; i < DIGIT; i++)
            {
                T[i] = '0';
            }
            printf("성공!\n");
            printf("* 1을 더한 후 : "); Show(T);
            free(P);
            break;
        }
        else
        {
            printf("문자열 탐색 실패.\n");
            d++;
            m--;
            free(P);
            continue;
        }
    }
}

// 메인함수는 걍 보여줄라고. 임시임.
int main()
{
    char* s = (char*)malloc(sizeof(char)*DIGIT);
    for (int i = 0; i < DIGIT; i++)
    {
        s[i] = '0';
    }
    makeString(s);
    free(s);
	return 0;
}