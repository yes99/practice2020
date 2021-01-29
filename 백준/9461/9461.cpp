#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    int n;
    int a;
    int i, j, k;
    long long dp[101];
    cin>>n;
    dp[1] = 1;
    dp[2] = 1;
    dp[3] = 1;
    /*
    for(i = 0 ; i <n ; i++)
    {
        for(j=4; j <=100; j++)
        {
            dp[j]= dp[j-3] + dp[j-2];
        }
    }
*/
    for (j = 4; j <= 100; j++)
    {
        dp[j] = dp[j - 3] + dp[j - 2];
    }
    int answer[101];

    for(i = 0 ; i < n ; i++)
    {
        cin >> j;
        answer[i] = j;
    }
    for(i=0;i<n;i++)
    {
        cout<<dp[answer[i]]<<endl;
    }
}
