#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
// A~Z 65~90   10~35
// 0~9   48~ 57
    string a;
    int b;
    cin >> a >> b;
    int l;
    int num =0;
    l = a.length();
    int cntl = l-1;
    int up, down;
    up = cntl;
    int point;
    int i , j, k;
    for(i = 0 ; i < l ; i++)
    {
        if(a[i]>=65)
        {
            down = a[i] - 55;
        }
        else
        {
            down = a[i] -48;
        }
        //cout << down << " " << b<< " " <<up <<" ";
        point= down  * pow(b, up);
        //cout << point << " ";
        num = num +  point;//pow(down , up);
        //cout << num << endl;
        up--;
    }
    cout << num;
}