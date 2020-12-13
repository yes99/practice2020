
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//내가 숫자 입력했으면 그게 오답이 아닌 이상 현재 넘버를 보내줘야함
//상대방이 그 넘버를 받아서 뭘 하느냐는 크게 문제가 안됨
//정답이면, 현재 넘버링을 보내주면 되지. 
//오답이면 그에 대가를 치루게 하게 하고 넘어가기. 

//보내줄 것은 현재 숫자. 

int main()
{
	int max = 999;
	int num;
	int cnt;	 //박수칠 횟수
	int a, b, c; //각 1 10 100의자리수
	int intanswer = 0;
	char* answer = (char*)malloc(sizeof(char) * 10);
	char* num_string = (char*)malloc(sizeof(char) * 10);
	int life = 3;
	printf("숫자 999까지 369게임을 진행합니다\n");
	printf("박수 칠만큼 c를 입력하세요\n");

	for (num = 1; num <= max; num++)
	{
		if (life == 0)
		{
			break;
		}
		cnt = 0;
		a = num % 10;
		b = (num % 100 - num % 10) / 10;
		c = num / 100;

		if (a % 3 == 0 && a > 0)
			cnt++;
		if (b % 3 == 0 && b > 0)
			cnt++;
		if (c % 3 == 0 && c > 0)
			cnt++;

		sprintf(num_string, "%d", num);
		printf("1초 안에 입력!\n");

		switch (cnt)
		{
		case 0:
			scanf("%d", &intanswer);
			if (intanswer == num)
			{
				printf("정답!\n");
				continue;
			}
			else
			{
				printf("오답!\n");
				num--;
				life--;
				continue;
			}
		case 1:
			scanf("%s", answer);
			if (strcmp(answer, "c") == 0)
			{
				continue;
			}
			else
			{
				printf("오답!\n");
				num--;
				life--;
				continue;
			}
		case 2:
			scanf("%s", answer);
			if (strcmp(answer, "cc") == 0)
				continue;
			else
			{
				printf("오답!\n");
				num--;
				life--;
				continue;
			}
		case 3:
			scanf("%s", answer);
			if (strcmp(answer, "ccc") == 0)
				continue;
			else
			{
				printf("오답!\n");
				num--;
				life--;
				continue;
			}
		}
	}


	return 0;
}
