#include <iostream>
#include <cstdio>

#define min(a, b) (a < b ? a : b)

using namespace std;

int main()
{
    int n, tmp;
    scanf("%d", &n);

    int two = 0, five = 0;
    for (int i = 1; i <= n; i++)
    {
        tmp = i;
        while (tmp)
        {
            if (tmp % 2 == 0)
            {
                two++;
                tmp /= 2;
            }
            else
                break;
        }

        tmp = i;
        while (tmp)
        {
            if (tmp % 5 == 0)
            {
                five++;
                tmp /= 5;
            }
            else
                break;
        }
    }
    printf("%d", min(two, five));
    return 0;
}
