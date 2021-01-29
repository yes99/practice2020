#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 1001;
int dp[MAX];
int cards[MAX];

int main()
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> cards[i];
    }
    for (int i = 1; i <= n; i++)   // i 가 카드 개수, dp[i]는 i개의 카드에서 얻을수 있는 최대값을 뜻한다.
    {
        for (int j = 1; j <= i; j++)  //j 가 dp구하려고 더 무엇을 해보려는거 파트. 
        {
            dp[i] = max(dp[i], dp[i - j] + cards[j]);
        }
    }
    cout << dp[n] << endl;

    return 0;
}