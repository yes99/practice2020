#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    int n , m ,e;
    int p[10000];
    cin >> n >> m >>e;
    int i , j ,k;
    int point;
    for(i = 0 ; i < n ; i++)
    {
        cin >> point;
        p[i] = point;
        p[i] = p[i] - e;
        //p[i] = abs(p[i]);
        //cout << p[i] << " ";
    }
    int plus[1000];
    int minus[1000];
    int cnt1 = 1;
    int cnt2 = 1;
    for(i = 0 ; i < n ; i++)
    {
        if(p[i] < 0)
        {
            minus[cnt1] = p[i];
            cnt1++;
        }
        else
        {
            plus[cnt2] = abs(p[i]);
            cnt2++;
        }
    }
    int min1, min2=1000000;
    for(i = 0; i<=cnt1 ; i++)
    {
        for(j = cnt2; j>=1 ; j--)
        {
            if(i+j ==n)
            {
                min1 = minus[i] + plus[j];
                min1 = min(min1 , min2);
            }
        }
    }
    cout << min1;
}