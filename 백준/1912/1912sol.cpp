#include <iostream>
#include <algorithm>

using namespace std;
int arr[100001] = {0,}; 
int dp[100001] = {0,};

int main()
{
    int n, i;
    cin >> n;
    for (i = 0; i < n; i++)
    {
        cin >> arr[i];
        dp[i] = arr[i];   //dp에 전부다 선언
    }
    int largest = dp[0];  //가장 큰 것 찾기
    for (i = 1; i < n; i++)
    {
        dp[i] = max(dp[i], dp[i - 1] + arr[i]);  //기존에 설정한 dp랑 그전꺼에다가 이번에 도는 arr을 더한거의 크기를 비교한다,   만약에 음수가 크게 나와서 후자가 나가리 되면 전자를 계속 유지한다. 
        if (dp[i] > largest)
        {
            largest = dp[i];
        }
    }
    cout << largest << endl;
    return 0;
}
