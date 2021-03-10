
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> // rand 함수를 위한 헤더 파일 
#include <time.h> // time 함수를 위한 헤더 파일 

int main()
{
	int user2Ball[3]; // 컴퓨터의 볼을 저장할 int형 배열 
	int i, j; // 반복을 위한 변수 
	int temp; // 난수 중복 체크를 위한 변수 
	int user1Ball[3]; // 사용자의 볼을 저장할 int형 배열 
	int count = 1; // 회차를 확인할 변수 9회까지 가능 
	int strike; // 스트라이크의 수를 세기 위한 변수 
	int ball; // 볼의 수를 세기 위한 변수 
		
	printf("당신은 방어팀 입니다\n");
	while (1) // 정상적인 숫자만 입력받기 위한 반복
	{
		
		printf("1부터 9까지의 숫자를 입력하세요 : ");

		scanf("%d %d %d", &user2Ball[0], &user2Ball[1], &user2Ball[2]);

		if (user2Ball[0] < 1 || user2Ball[0] > 9 || user2Ball[1] < 1 || user2Ball[1] > 9 || user2Ball[2] < 1 || user2Ball[2] > 9)

		{ // 입력한 숫자가 1 ~ 9 숫자가 아니면 다시 입력받도록 

			printf("범위 외의 숫자를 입력하시면 안됩니다.\n");

			continue;

		}

		else if (user2Ball[0] == user2Ball[1] || user2Ball[0] == user2Ball[2] || user2Ball[1] == user2Ball[2])

		{ // 입력한 숫자 중에 중복된 게 있으면 다시 입력받도록 

			printf("중복된 숫자를 입력하시면 안됩니다.\n");

			continue;

		}

		break; // 아무 문제 없을 경우 반복 종료 

	}


	printf("당신은 공격팀 입니다\n");
	while (1) // 숫자야구 게임 시작 

	{

		printf("[%d회차 숫자야구]\n", count);

		while (1) // 정상적인 숫자만 입력받기 위한 반복 

		{

			printf("1부터 9까지의 숫자를 입력하세요 : ");

			scanf("%d %d %d", &user1Ball[0], &user1Ball[1], &user1Ball[2]);

			if (user1Ball[0] < 1 || user1Ball[0] > 9 || user1Ball[1] < 1 || user1Ball[1] > 9 || user1Ball[2] < 1 || user1Ball[2] > 9)

			{ // 입력한 숫자가 1 ~ 9 숫자가 아니면 다시 입력받도록 

				printf("범위 외의 숫자를 입력하시면 안됩니다.\n");

				continue;

			}

			else if (user1Ball[0] == user1Ball[1] || user1Ball[0] == user1Ball[2] || user1Ball[1] == user1Ball[2])

			{ // 입력한 숫자 중에 중복된 게 있으면 다시 입력받도록 

				printf("중복된 숫자를 입력하시면 안됩니다.\n");

				continue;

			}

			break; // 아무 문제 없을 경우 반복 종료 

		}

		ball = 0;

		strike = 0;

		for (i = 0; i < 3; i++) // computerBall 1~3번째에 따라 각 userBall 1~3번째를 확인하기 위한 반복 

			for (j = 0; j < 3; j++)

				if (user2Ball[i] == user1Ball[j]) // computerBall과 userBall의 값이 같다면 

					if (i == j) // 같은 위치일 경우 

						strike++; // 스트라이크 개수 증가 

					else // 다른 위치일 경우 

						ball++; // 볼 개수 증가 

  // 확인한 결과를 출력 

		printf("[결과]스트라이크 : %d, 볼 : %d\n\n", strike, ball);

		if (strike == 3) // 만약 스트라이크 개수가 3개이면 승리 

		{

			printf("***** 승리했습니다. *****\n\n");

			break;

		}

		else if (count == 9) // 만약 9회차인데도 승리하지 못하면 패배 

		{

			printf("***** 패배했습니다.. 정답 : %d %d %d *****\n\n", user2Ball[0], user2Ball[1], user2Ball[2]);

			break;

		}

		count++;

	}

	return 0;

}
