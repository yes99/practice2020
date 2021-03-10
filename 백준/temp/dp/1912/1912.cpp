#include <iostream>
#include <algorithm>

using namespace std;

int main()
{

    int n;
    int dp[1000] = {};
    int arr[1000] = {};
    int sum = -99999999;
    //int sum[100][100] = {0, };
    //int sumA[1000] = {};
    cin >> n;
    int former = 0, latter = 0;
    int dpf[1000], dpl[1000];
    int maxf= 0, maxl = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    for (int i = 0; i < n; i++)
    {
        maxl = arr[i];
        /*for (int j = 0; j < i; j++)
        {
           former = former + arr[j];
           dpf[i]= former;
           maxf = max(maxf, dpf[i]);
        }*/

        for(int j = i+1 ; j <n ; j++)
        {
           latter = latter + arr[j];
           dpl[i]= latter;
           maxl = max(maxl, dpl[i]);
        }
        //dp[i] = dp[i] + maxf + maxl;
        dp[i] = dp[i] + maxl;
        sum = max(sum, dp[i]);
        former = 0;
        latter = 0;
        maxl = 0;

    }
 
    for (int i = 0; i < n; i++)
    {
        //cout<< dp[i]<< " "; 
    }
    cout <<sum;
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
   /* for(int i = 0 ; i < n ; i++)
    {
        sumA[i] = dp[i] + dp2[i];
        large = max(large, sumA[i]);
    }
    cout<<large-1;*/
}