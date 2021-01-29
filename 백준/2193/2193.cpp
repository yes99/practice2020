#include <iostream>
using namespace std;

int main()
{

    long long dp[101][2] = {};
    int n;
    long long sum = 0;

    cin >> n;

    dp[1][0] = 0;
    dp[1][1] = 1; 

    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0)
            {
                dp[i][0] = dp[i - 1][1]+dp[i-1][0];
            }
            else if (j == 1)
            {
                dp[i][1] = dp[i - 1][0];
            } 
        }
    }
    for (int i = 0; i < 2; i++)
    {
        sum = (sum + dp[n][i]);
    }
    cout << sum ;
}