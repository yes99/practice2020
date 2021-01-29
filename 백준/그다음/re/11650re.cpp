#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
using namespace std;

struct point
{
    int x;
    int y;
}p;


bool compare(point a, point b)
{
    if (a.x == b.x)
    {
        return a.y < b.y;
    }
    else
    {
        return a.x < b.x;
    }
}

int main()
{
    int N, x, y;
    point p[100000];
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &x, &y);
        p[i].x = x;
        p[i].y = y;
    }

    sort(p, p+N, compare);

    for (int i = 0; i < N; i++)
        printf("%d %d\n", p[i].x, p[i].y);
}
