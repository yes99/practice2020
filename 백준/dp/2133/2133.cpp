#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    int N;
    int dp[31];
    cin >> N;
    dp[0] = 1;
    dp[2] = 3;
    if (N % 2 == 1)
        dp[N] = 0;
    else
    {
        for (int i = 4; i <= N; i += 2)
        {
            dp[i] = 3 * dp[i - 2];   // 곱해줘야함, 곱해줘야지 이전 결과에 새로운 결과 모두 합한 경우의수가 다 나옴
            for (int j = 4; j <= i; j += 2)
            {
                dp[i] = dp[i] + 2 * dp[i - j]; // 마찬가지로 앞에 있는 애들 다 들볶으면서 뒤에 두가지 경우의 수 모두 나오려면 곱하기 하는게 맞음
            }
        }
    }
    cout << dp[N] << '\n';
    return 0;
}
