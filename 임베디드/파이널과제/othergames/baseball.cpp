
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> // rand �Լ��� ���� ��� ���� 
#include <time.h> // time �Լ��� ���� ��� ���� 

int main()
{
	int user2Ball[3]; // ��ǻ���� ���� ������ int�� �迭 
	int i, j; // �ݺ��� ���� ���� 
	int temp; // ���� �ߺ� üũ�� ���� ���� 
	int user1Ball[3]; // ������� ���� ������ int�� �迭 
	int count = 1; // ȸ���� Ȯ���� ���� 9ȸ���� ���� 
	int strike; // ��Ʈ����ũ�� ���� ���� ���� ���� 
	int ball; // ���� ���� ���� ���� ���� 
		
	printf("����� ����� �Դϴ�\n");
	while (1) // �������� ���ڸ� �Է¹ޱ� ���� �ݺ�
	{
		
		printf("1���� 9������ ���ڸ� �Է��ϼ��� : ");

		scanf("%d %d %d", &user2Ball[0], &user2Ball[1], &user2Ball[2]);

		if (user2Ball[0] < 1 || user2Ball[0] > 9 || user2Ball[1] < 1 || user2Ball[1] > 9 || user2Ball[2] < 1 || user2Ball[2] > 9)

		{ // �Է��� ���ڰ� 1 ~ 9 ���ڰ� �ƴϸ� �ٽ� �Է¹޵��� 

			printf("���� ���� ���ڸ� �Է��Ͻø� �ȵ˴ϴ�.\n");

			continue;

		}

		else if (user2Ball[0] == user2Ball[1] || user2Ball[0] == user2Ball[2] || user2Ball[1] == user2Ball[2])

		{ // �Է��� ���� �߿� �ߺ��� �� ������ �ٽ� �Է¹޵��� 

			printf("�ߺ��� ���ڸ� �Է��Ͻø� �ȵ˴ϴ�.\n");

			continue;

		}

		break; // �ƹ� ���� ���� ��� �ݺ� ���� 

	}


	printf("����� ������ �Դϴ�\n");
	while (1) // ���ھ߱� ���� ���� 

	{

		printf("[%dȸ�� ���ھ߱�]\n", count);

		while (1) // �������� ���ڸ� �Է¹ޱ� ���� �ݺ� 

		{

			printf("1���� 9������ ���ڸ� �Է��ϼ��� : ");

			scanf("%d %d %d", &user1Ball[0], &user1Ball[1], &user1Ball[2]);

			if (user1Ball[0] < 1 || user1Ball[0] > 9 || user1Ball[1] < 1 || user1Ball[1] > 9 || user1Ball[2] < 1 || user1Ball[2] > 9)

			{ // �Է��� ���ڰ� 1 ~ 9 ���ڰ� �ƴϸ� �ٽ� �Է¹޵��� 

				printf("���� ���� ���ڸ� �Է��Ͻø� �ȵ˴ϴ�.\n");

				continue;

			}

			else if (user1Ball[0] == user1Ball[1] || user1Ball[0] == user1Ball[2] || user1Ball[1] == user1Ball[2])

			{ // �Է��� ���� �߿� �ߺ��� �� ������ �ٽ� �Է¹޵��� 

				printf("�ߺ��� ���ڸ� �Է��Ͻø� �ȵ˴ϴ�.\n");

				continue;

			}

			break; // �ƹ� ���� ���� ��� �ݺ� ���� 

		}

		ball = 0;

		strike = 0;

		for (i = 0; i < 3; i++) // computerBall 1~3��°�� ���� �� userBall 1~3��°�� Ȯ���ϱ� ���� �ݺ� 

			for (j = 0; j < 3; j++)

				if (user2Ball[i] == user1Ball[j]) // computerBall�� userBall�� ���� ���ٸ� 

					if (i == j) // ���� ��ġ�� ��� 

						strike++; // ��Ʈ����ũ ���� ���� 

					else // �ٸ� ��ġ�� ��� 

						ball++; // �� ���� ���� 

  // Ȯ���� ����� ��� 

		printf("[���]��Ʈ����ũ : %d, �� : %d\n\n", strike, ball);

		if (strike == 3) // ���� ��Ʈ����ũ ������ 3���̸� �¸� 

		{

			printf("***** �¸��߽��ϴ�. *****\n\n");

			break;

		}

		else if (count == 9) // ���� 9ȸ���ε��� �¸����� ���ϸ� �й� 

		{

			printf("***** �й��߽��ϴ�.. ���� : %d %d %d *****\n\n", user2Ball[0], user2Ball[1], user2Ball[2]);

			break;

		}

		count++;

	}

	return 0;

}
