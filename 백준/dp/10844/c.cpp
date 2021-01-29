#include <iostream>

using namespace std;

int main()
{
    int array[2][10];
    int a = 0; //현재배열
    int b = 1; //다음배열
    int c;
    scanf("%d", &c);
    //초기화
    for (int i = 0; i < 10; i++)
    {
        array[0][i] = 1;
        array[1][i] = 0;
    }
    array[0][0] = 0;
    int sum = 0;
    if (c == 1)
    {
        sum = 9;
    }
    if (c > 1)
    {
        for (int i = 1; i < c; i++)
        {
            for (int k = 0; k < 10; k++)
            {
                array[b][k] = 0;
                array[a][k] = array[a][k] % 1000000000;
            }
            for (int j = 0; j < 10; j++)
            {
                if (j == 0)
                {
                    array[b][j + 1] = array[b][j + 1] % 1000000000 + array[a][j] % 1000000000;
                }
                else if (j == 9)
                {
                    array[b][j - 1] = array[b][j - 1] % 1000000000 + array[a][j] % 1000000000;
                }
                else if (j < 9 && j > 0)
                {
                    array[b][j - 1] = array[b][j - 1] % 1000000000 + array[a][j] % 1000000000;
                    array[b][j + 1] = array[b][j + 1] % 1000000000 + array[a][j] % 1000000000;
                }
            }
            //현재배열과 다음 배열을 바꿔주기
            if (a == 0)
            {
                a = 1;
                b = 0;
            }
            else if (a == 1)
            {
                a = 0;
                b = 1;
            }
        }
        //sum을 처리
        for (int i = 0; i < 10; i++)
        {
            sum = (sum + array[a][i]) % 1000000000;
        }
    }
    printf("%d", sum % 1000000000);
    return 0;
}