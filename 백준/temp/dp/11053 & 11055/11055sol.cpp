#include <iostream>
#include <algorithm>
using namespace std;
int num, arr[1001], dp[1001], sum;
int main()
{
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cin >> arr[i];
        dp[i] = arr[i];
    }

    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j])
            {
                dp[i] = max(dp[j] + arr[i], dp[i]);
            }
        }
        sum = max(dp[i], sum);
    }
    /*for(int i = 1 ; i <= num ; i++)
    {
        cout<< dp[i] << " ";
    }
    /*cout<<endl;
    for(int i = 1 ; i <= num ; i++)
    {
        //cout<< ss[i] << " ";
    }*/
    cout << sum << endl;
    return 0;
}
