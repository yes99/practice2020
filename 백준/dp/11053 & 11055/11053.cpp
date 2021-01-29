#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int num;
    int a;
    int arr[1001];
    int dp[1001];
    int i, j ,k;
    cin >> num;
    for(i =1; i <=num; i++)
    {
        cin >> a;
        arr[i] = a;
    }
    int cnt = 1;
    int largest = 0;
    int sum = 0;
    for(i = 1; i <=num;i++)
    {
        dp[i] = 1;
        for(j =1; j<i;j++)
        {
            if(arr[i]>arr[j])
            {
				dp[i] = max(dp[i], dp[j] + 1);
            }
        }
     	sum = max(sum, dp[i]);
    }
    cout<<sum<<endl;
    for(int i = 1 ; i <= num ; i++)
    {
        cout<< dp[i] << " ";
    }
}