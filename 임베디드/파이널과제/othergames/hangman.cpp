#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>



int main(void)
{
	char ch;
	int cnt = 0;

	//  등록된 단어 사전​
	const char *dic[] = {"boy","good","student", "university", "chair", "desk", "computer", "mask", "holiday" };
	int wnum = sizeof(dic) / sizeof(char *);  // 등록된 단어의 개수
	int i;
	int sel;
	const char *word;
	char *pword;
	int len;



	srand(time(NULL));     // 난수 시드 조정
	sel = rand() % wnum;   // 임의의 단어 첨자
	word = dic[sel];          // 임의의 단어 포인터

	len = strlen(word);       // 단어의 길이

	pword = (char *)malloc(len + 1);   // 화면에 나타나는 단어 배열

	for (i = 0; i < len; i++)
		pword[i] = '_';     //  화면에 나타나는 단어 _ 로 초기화
	pword[len] = '\0';



	printf("== 단어 맞추기 게임 ==\n");

	while (1) {
		printf("\n맞출단어 : %s  ", pword);
		printf(" 빈칸에 들어갈 문자 입력 :");
		scanf(" %c", &ch); 
		fflush(stdin);   //  문자입력
		cnt++;                                    // 시도 회수 카운트



		for (i = 0; i < len; i++)
			if (pword[i] == '_' && word[i] == ch)   // 입력된 문자가 아직 가려져 있으면
				pword[i] = ch;                          // 화면에 그 문자를 나타냄



		for (i = 0; i < len; i++)

			if (pword[i] == '_') break;       //  가려져 있는 문자가 있는가?   

		if (i == len) {    // 가려진 문자가 없으면, 즉 다 맞추었으면
			printf("\n%d 번만에 %s를 맞추었습니다.\n\n", cnt, pword);
			return 0;
		}

	}
	return 0;
}