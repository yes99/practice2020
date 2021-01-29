#include <iostream>
#include <algorithm>
using namespace std;

int score[301];
int dp[301][2];    
//[][0] 한번 연속  [][1] 두번 연속

int main(void)
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        cin >> score[i];
    }
    dp[1][0] = score[1];

    for (int i = 2; i <= n; ++i)
    {
        dp[i][1] = dp[i - 1][0] + score[i];    //이미 두번 연속된거를 정하는 거여서, 앞에꺼에서만 더하기 가능
        dp[i][0] = max(   dp[i - 2][1],      dp[i - 2][0]) + score[i];   //이미 연속된 전전꺼라서 뭘 하더라도 상관 없음
    }
    cout <<max(dp[n][0], dp[n][1]);

}