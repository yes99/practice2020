#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define DIGIT 6
char str[17] = "0123456789ABCDEF";


// ���� ���� ���ڿ��� ���� ����ϴ� �Լ�.
void Show(char* data)
{
    for (int i = 0; i < DIGIT; i++)
        printf("%c", data[i]);
    printf("\n");
}

// ó���� ���� ���ڿ��� ����� �Լ�.
// ���⼭ ���� ���ڿ��� �ؽ� �Լ��� �Է��Ͽ� �ؽð��� �����.
char* MakePW()
{
    char* pw = (char*)malloc(sizeof(char) * DIGIT);
    for (int i = 0; i < DIGIT; i++)
        pw[i] = str[rand() % 16];
    return pw;
}



// �ؽð��� ���� ���� ���ڿ��� ã�� �Լ��� ����.
// ���ڴ� ������ ���� �޾ƾ� �Ѵ�. 1. �ؽ� ���̺�, 2. �ؽð��� ����
// ������ �ӽ÷� pwString�̶�� ���ڸ� �޾Ҵµ� �̰� �����ؾ���.
// �ϴ� �װ� ���ֺ���.
void decoding(char* pwString)
{
    int i = 0;
    char* inputString = (char*)malloc(sizeof(char) * DIGIT);
    for (i = 0; i < DIGIT; i++)
        inputString[i] = str[0];
    // inputString�� �ʱ갪�� 000000���� �ʱ�ȭ
    int sameCount = 0;
    clock_t st = clock();
    while (1)
    {
        /////////////////////////////////////////////////////////////

        // �� �κп� inputString�� 1�� �ø��� �κ��� �߰��ؾ� ��.
        // ÷���� �ٸ� �ҽ����Ͽ� �� �Լ��� �ִµ� ����� �Űܾ��ҵ�
        // �׳� °�� ���ٺ��̸� �ȵǰ� �����ϰ� ��ȯ���� �Űܾ��ҵ�

        //////////////////////////////////////////////////////////////

        // ������ inputString�� �ؽ����̺��� ���� ���ϴ� �κ�.
        // ��� �ؽ����̺�� ���� �ٸ��� break�Ͽ� �ٽ� ������ ����.
        // ��ġ�ϴ� �ؽð��� ������ ��� �� �ӽù迭�� �����Ѵ�.
        for (int i = 0; i < DIGIT; i++)
        {
            if (pwString[i] == inputString[i])
            {
                sameCount++;
                continue;
            }
            else
            {
                //printf("��ȣ �ص� ����...\n");
                sameCount = 0;
                break;
            }
        }
        if (sameCount == DIGIT)
        {
            printf("Notice : ��ȣ �ص��� �����߽��ϴ�!!\n");
            printf("��ȣ >>> "); Show(inputString);
            free(inputString);
            break;
        }
    }
    clock_t ed = clock();
    printf("Notice : �ɸ� �ð� %dms\n", ed - st);
}

int main(int argc, char* argv[])
{
    srand((unsigned int)time(NULL));
    int zz;
    char* pwString = MakePW();
    printf("������ ��ȣ>>> ");  Show(pwString);
    printf("�����Ϸ��� �ƹ� Ű�� �Է��ϼ���.\n");
    scanf("%d", &zz);
    decoding(pwString);

    free(pwString);
    return 0;
}

