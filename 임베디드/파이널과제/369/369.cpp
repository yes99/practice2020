
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//���� ���� �Է������� �װ� ������ �ƴ� �̻� ���� �ѹ��� ���������
//������ �� �ѹ��� �޾Ƽ� �� �ϴ��Ĵ� ũ�� ������ �ȵ�
//�����̸�, ���� �ѹ����� �����ָ� ����. 
//�����̸� �׿� �밡�� ġ��� �ϰ� �ϰ� �Ѿ��. 

//������ ���� ���� ����. 

int main()
{
	int max = 999;
	int num;
	int cnt;	 //�ڼ�ĥ Ƚ��
	int a, b, c; //�� 1 10 100���ڸ���
	int intanswer = 0;
	char* answer = (char*)malloc(sizeof(char) * 10);
	char* num_string = (char*)malloc(sizeof(char) * 10);
	int life = 3;
	printf("���� 999���� 369������ �����մϴ�\n");
	printf("�ڼ� ĥ��ŭ c�� �Է��ϼ���\n");

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
		printf("1�� �ȿ� �Է�!\n");

		switch (cnt)
		{
		case 0:
			scanf("%d", &intanswer);
			if (intanswer == num)
			{
				printf("����!\n");
				continue;
			}
			else
			{
				printf("����!\n");
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
				printf("����!\n");
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
				printf("����!\n");
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
				printf("����!\n");
				num--;
				life--;
				continue;
			}
		}
	}


	return 0;
}
