#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    int dp[1000] = {};
    int arr[1000] = {};
    int sum = -99999999;
    cin >> n;
    int former = 0, latter = 0;
    //int dpf[1000], dpl[1000];
    int maxf= 0, maxl = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        dp[i] = arr[i];
    }

    for (int i = 0; i < n; i++)
    {
    

        for(int j = i+1 ; j <n ; j++)
        {
           dp[i]= dp[i] + arr[j];
           maxl = max(maxl, dp[i]);
        }
        dp[i] = dp[i] + maxl;
        sum = max(sum, dp[i]);
        former = 0;
        latter = 0;
        maxl = 0;

    }
 
    cout <<sum;

}