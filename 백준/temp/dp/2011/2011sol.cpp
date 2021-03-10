#include <iostream>
#include <string>
#define mod 1000000
using namespace std;

int main()
{
    string s;
    cin >> s;
    int size = s.size();
    if (s[0] == '0')  // 절대 일어나지 않겠지만 0인경우
    {
        cout << 0;
        return 0;
    }
    int dp[5001];
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= size; i++)
    {
        if (s[i - 1] > '0')
        {
            dp[i] = dp[i - 1] % mod; //s의 현재값(i-1)이 0이 아닐 때
        }
        int over = (s[i - 2] - '0') * 10 + s[i - 1] - '0'; //s[i-2 ~ i-1]이 10~26일 때
        if (over >=10 && over <= 26)
        {
            dp[i] = (dp[i] + dp[i - 2]) % mod;
        }
    }
    cout << dp[size];
}
