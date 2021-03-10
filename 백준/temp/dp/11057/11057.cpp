#include <iostream>
using namespace std;

int main()
{

    int dp[101][10] = {
        0,
    };
    int n;
    int sum = 0;
    int k;
    cin >> n;

    for (int i = 0; i < 10; i++)
        dp[1][i] = 1;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (j == 0)
            {
                for (k = 9; k >= j; k--)
                {
                    dp[i][j] = (dp[i][j] + dp[i - 1][k])%10007;
                }
            }
            else if (j == 1)
            {
                for (k = 9; k >= j; k--)
                {
                    dp[i][j] = (dp[i][j] + dp[i - 1][k])%10007;
                }
            }
            else if (j == 2)
            {
                for (k = 9; k >= j; k--)
                {
                    dp[i][j] = (dp[i][j] + dp[i - 1][k])%10007;
                }
            }
            else if (j == 3)
            {
                for (k = 9; k >= j; k--)
                {
                    dp[i][j] = (dp[i][j] + dp[i - 1][k])%10007;
                }
            }
            else if (j == 4)
            {
                for (k = 9; k >= j; k--)
                {
                    dp[i][j] = (dp[i][j] + dp[i - 1][k])%10007;
                }
            }
            else if (j == 5)
            {
                for (k = 9; k >= j; k--)
                {
                    dp[i][j] = (dp[i][j] + dp[i - 1][k])%10007;
                }
            }
            else if (j == 6)
            {
                for (k = 9; k >= j; k--)
                {
                    dp[i][j] = (dp[i][j] + dp[i - 1][k])%10007;
                }
            }
            else if (j == 7)
            {
                for (k = 9; k >= j; k--)
                {
                    dp[i][j] = (dp[i][j] + dp[i - 1][k])%10007;
                }
            }
            else if (j == 8)
            {
                for (k = 9; k >= j; k--)
                {
                    dp[i][j] = (dp[i][j] + dp[i - 1][k])%10007;
                }
            }
            else
            {
                for (k = 9; k >= j; k--)
                {
                    dp[i][j] = (dp[i][j] + dp[i - 1][k])%10007;
                }
            }
        }
    }
    for (int i = 0; i < 10; i++)
    {
        sum = (sum + dp[n][i])%10007;
    }
    cout << sum %10007;
}