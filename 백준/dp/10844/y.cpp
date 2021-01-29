#include <stdio.h>

long long dp_array[101][10] = {
    0,
};

int main(void)
{
    int N = 0;

    scanf("%d", &N);

    dp_array[0][1] = 1;
    dp_array[1][0] = 0;
    for (int i = 1; i <= 9; i++)
        dp_array[1][i] = 1;

    for (int i = 2; i <= N; i++)
        for (int j = 1; j <= 9; j++)
        {
            if (j == 1)
                dp_array[i][j] = (dp_array[i - 2][j] + dp_array[i - 1][j + 1]) % 1000000000;
            else if (j == 9)
                dp_array[i][j] = dp_array[i - 1][j - 1] % 1000000000;
            else
                dp_array[i][j] = (dp_array[i - 1][j - 1] + dp_array[i - 1][j + 1]) % 1000000000;
        }

    long long result = 0;

    for (int i = 1; i <= 9; i++)
        result = (result + dp_array[N][i]) % 1000000000;

    printf("%lld\n", result);

    return 0;
}