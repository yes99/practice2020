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
    int ss[1001];
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
    }
    //cout<<sum<<endl;
    for(i = 1; i <=num; i++)
    {
        ss[i]= arr[i];
        for(j = i; j>=1;j--)
        {
            if(dp[j]==(dp[i]-1))
            {
                if(arr[j]<arr[i])
                {
                    ss[i] = ss[j]+ss[i];
                }
            }
        if(dp[j]==1)
        {
            break;
        }
        }
        
        largest = max(largest , ss[i]);
  
    }
    for(int i = 1 ; i <= num ; i++)
    {
        cout<< dp[i] << " ";
    }
    cout<<endl;
    for(int i = 1 ; i <= num ; i++)
    {
        cout<< ss[i] << " ";
    }
    cout<<endl << largest;
    //cout<<largest;
}