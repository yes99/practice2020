#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

typedef struct _INFO_
{
    int x;
    int y;
}INFO;

INFO info[100001];

bool comp(const INFO& a, const INFO& b)
{
    if (a.y != b.y)
        return a.y < b.y;
    else if (a.y == b.y)
    {
        return a.x < b.x;
    }
}

int main()
{
    int n;
    cin >> n;;

    for (int i = 0; i < n; i++)
        cin >> info[i].x >> info[i].y;
    
    sort(info, info + n, comp);

    for (int i = 0; i < n; i++)
        cout << info[i].x <<" "<< info[i].y<<endl;

    return 0;
}
