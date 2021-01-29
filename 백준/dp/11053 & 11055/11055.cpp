#include <iostream>

using namespace std;

int main()
{
    int num;
    int a;
    int arr[1001];
    int i, j ,k;
    cin >> num;
    for(i =1; i <=num; i++)
    {
        cin >> a;
        arr[i] = a;
    }
    int sum = 0;
    int cnt = 0;
    int start = arr[1];
    for(i = 2; i <=num;i++)
    {
        if(arr[i]>start)
        {
            cnt++;
            start = arr[i];
            sum = sum + start;
            //cout << start<<endl;
        }
        /*else
        {
            cnt =0;
            start = arr[i];
        }*/
        
        
    }
    //cout<<cnt+1;
    cout<<sum;
}