#include <iostream>
int min(int, int);
int finding[1000001];

int main()
{
    finding[1] = 0;
    finding[2] = 1;
    finding[3] = 1;
    int a;
    scanf("%d", &a);

    if (a >= 4)
    {
        for (int i = 4; i <= a; i++)
        {
            finding[i] = finding[i - 1] + 1;
            if (i % 3 == 0)
            {
                finding[i] = min(finding[i], finding[i / 3] + 1);
            }
            if (i % 2 == 0)
            {
                finding[i] = min(finding[i], finding[i / 2] + 1);
            }
        }
    }
    printf("%d", finding[a]);
    return 0;
}

int min(int c, int d)
{
    if (c >= d)
        return d;
    else if (c < d)
        return c;
}