#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100
int main(void)
{
    FILE* fp1;
    FILE* fp2;
    char a[SIZE];
    char b[SIZE];
    char f1[SIZE];
    char f2[SIZE];
    int bytes = 0;
    printf("ù��° ���� �̸�: ");
    gets(a);
    printf("�ι�° ���� �̸�: ");
    gets(b);
    if ((fp1 = fopen(a, "r")) == NULL)
    {
        fprintf(stderr, "���� ���� ����1\n");
        exit(1);
    }
    if ((fp2 = fopen(b, "r")) == NULL)
    {
        fprintf(stderr, "���� ���� ����2\n");
        exit(1);
    }
    while (1)
    {
        fgets(f1, sizeof(f1), fp1); //fgets�� \n(���๮��) ���� ������ ���ڿ��� ���� 
        fgets(f2, sizeof(f2), fp2);
        if (strcmp(f1, f2) != 0) // f1�� ũ�� ��, f2�� ũ�� ��, ������ 0
        {
            printf("<< %s\n", f1);
            printf(">> %s\n", f2);
            break;
        }
        if (feof(fp1) != 0) // ������ ���̸� not0, ���� �ƴϸ� 0
        {
            printf("������ ���� ��ġ��\n");
            break;
        }
    }
    return 0;
}


