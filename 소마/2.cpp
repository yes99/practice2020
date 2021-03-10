#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    int p , n , h;
    cin >>p >> n >> h;
    int i , j ,k;
    int x, y;
    int cnt = 0;
    int formerx = 1;
    int array[100][100] = { {0, } ,};
    for(i= 0 ; i < n ; i++)
    {
        cin >> x  >> y;
        array[x][cnt] = y;
        cnt++;
        if(formerx != x)
        {
            cnt = 0;
        }
        formerx = x;
    }
    for(i= 0 ; i < n ; i++)
    {
        sort(array[i], array[i]+100);
    }
    int dp[100];
    int answer;
    for(i=0; i < n ; i++)
    {
        for(j=1;j<100;j++)
        {
            dp[i] = array[i][j] + array[i][j-1];
            if(dp[i]> h && array[i][j]<h)
            {
                answer = max(dp[i], array[i][j]);
                break;
            }
        }
        cout << answer <<endl;
    }


    /*for(i =0; i < 3; i++)
    {
        for(j=0; j<100;j++)
        {
            cout << array[i][j] << " ";
        }
        cout<<endl;
    }*/
}