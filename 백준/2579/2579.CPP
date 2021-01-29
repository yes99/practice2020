#include <iostream>
#include <algorithm> 

using namespace std;

int main()
{

	int n;
	int stair[10010] = {};
	int dp[10010] = {};
	cin >> n;
	
	for (int i = 1; i <= n; i++)
		cin >> stair[i];
	
	//초기값 설정
	for (int i = 1; i < 3 && i <= n; i++) 
    {
		if (i == 1)
			dp[i] = stair[i];
		else
			dp[i] = stair[i] + stair[i - 1];
	}
	dp[1] = stair[1];
    dp[2]



	//dp 알고리즘
	for (int i = 3; i <= n; i++) {
		int result = 0;
		dp[i]= max(dp[i - 3] + stair[i] + stair[i - 1], dp[i - 2] + stair[i]);
		dp[i]= max(dp[i - 1], dp[i]);
		
	}

	cout << dp[n];
}
