#include <iostream>
#include <algorithm>

using namespace std;

int main()
{

    int n;
    int dp[1000] = {};
    int arr[1000] = {};
    int dp2[1000] = {};
    int sum = 0;
    int sumA[1000] = {};
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;

        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    for (int i = n-1; i >= 0; i--)
    {
        dp2[i] = 1;

        for (int j = n-1; j > i; j--)
        {
            if (arr[i] > arr[j])
            {
                dp2[i] = max(dp2[i], dp2[j] + 1);
            }
        }
    }
    //cout << sum << endl;
    int large = 0;
    /*for (int i = 0; i < n; i++)
    {
        cout << dp[i] << " ";
    }cout<<endl;
    for (int i = 0; i < n; i++)
    {
        cout << dp2[i] << " ";
    }cout<<endl;*/
    for(int i = 0 ; i < n ; i++)
    {
        sumA[i] = dp[i] + dp2[i];
        large = max(large, sumA[i]);
    }
    cout<<large-1;
}