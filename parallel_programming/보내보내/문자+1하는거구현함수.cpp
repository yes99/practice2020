#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIGIT 6

// ���� �������Ͽ� �Űܾ� �ϴ� �Լ��� BF_matching�� makeString�̴�.
// makeString�� �̸��� �� �̻��Ѱ�?? ������ �̸� �������� ������.
// ������ 0~9�� ��쿡 �ۼ��ѰŶ� 0~f�� 16������ �ٲ���Ѵ�.
// ������ 9�� ������ ������ ����������
// 16�����̸� f�� ������ �����̰���??

void Show(char* s)
{
    for (int i = 0; i < DIGIT; i++)
    {
        printf("%c", s[i]);
    }
    printf("\n");
}


// �Űܾ� �ϴ� �Լ� 1.
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

// �Űܾ� �ϴ� �Լ� 2.
void makeString(char* T)
{
    T[0] = '9';
    T[1] = '9';
    T[2] = '9';
    T[3] = '1';
    T[4] = '9';
    T[5] = '8';
    printf("* ���� T : "); Show(T);
    int m = DIGIT; // P�� �ڸ���.
    int d = 0;      
    while (1)
    {
        // ���������� XXX999�� �ƴ� ���.
        // ���ڿ��� ������ �ڸ��� +1�Ѵ�.
        if (m == 0)
        {
            printf("���� ����.\n");
            T[DIGIT - 1]++;
            printf("* 1�� ���� �� : "); Show(T);
            return;
        }

        // T�� ���� P�� ����.
        char* P = (char*)malloc(sizeof(char) * m);
        for (int i = 0; i < m; i++)
        {
            P[i] = '9';
        }
        
        // XXX999 ���� Ȯ�� �� inputString++ �� �ϴ� �ܰ�.
        bool right = BF_matching(T, DIGIT, P, m);
        // XXX999�� ���
        if (right == true)
        {   // 999999 �϶� ���� ó��.
            if (m == DIGIT)
            {
                printf("�ִ� ���ڿ� �����߽��ϴ�. �� �κ� �����ϼ���!!\n");
                return;
            }
            // ex) 199999 => 200000 ���� �ٲٴ� ����.
            else
            {
                T[d - 1]++;
            }
            for (int i = d; i < DIGIT; i++)
            {
                T[i] = '0';
            }
            printf("����!\n");
            printf("* 1�� ���� �� : "); Show(T);
            free(P);
            break;
        }
        else
        {
            printf("���ڿ� Ž�� ����.\n");
            d++;
            m--;
            free(P);
            continue;
        }
    }
}

// �����Լ��� �� �����ٶ��. �ӽ���.
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