#include <iostream>
#include <cstdio>

#define min(a, b) (a < b ? a : b)
using namespace std;

long long C(int a, int b)
{
    int i;
    int result;
    long long mul = 1, div = 1;
    int cnt = 1;
    for (i = 0; i < b; i++)
    {
        mul = mul * a;
        a--;
    }
    for (i = 0; i < b; i++)
    {
        div = div * cnt;
        cnt++;
    }
    //cout << mul << " " << div<<endl;;
    result = mul / div;
    //cout << result;
    return result;
}

int main()
{
    int a, b;
    cin >> a >> b;
    long long r;
    r = C(a, b);
    int tmp;
    int two = 0, five = 0;
    int i, j, k;
    int cnt = 0;
    //cout << r << endl;
    while (1)
    {
        if (r % 2 == 0)
        {
            two++;
            r /= 2;
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        if (r % 5 == 0)
        {
            five++;
            r /= 5;
        }
        else
        {
            break;
        }
    }
    //cout << five << endl;
   // cout << two << endl;
    printf("%d", min(two, five));
    return 0;
}
