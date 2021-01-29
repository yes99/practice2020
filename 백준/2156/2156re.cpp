#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int num;
    int wine[10001];
    int i, j, k, z;
    int amount;
    cin >> num;
    for (i = 1; i <= num; i++)
    {
        cin >> amount;
        wine[i] = amount;
    }

    //case1 첫번째 수 포함
    int sum1;
    int temp1 = 0;
    for (z = 1; z < num - 3; z++)
    {
        for (i = z + 2; i <= num - 2; i++)
        {
            for (j = i + 1; j <= num - 1; j++)
            {
                for (k = j + 1; k <= num; k++)
                {
                    sum1 = wine[z] + wine[i] + wine[j] + wine[k];
                    if (j == i + 1 && k == i + 2)
                    {
                        sum1 = 0;
                    }
                    temp1 = max(temp1, sum1);
                }
            }
        }
    }
    int sum2;
    int temp2 = 0;
    for (z = 2; z <= num - 3; z++)
    {
        for (i = z+2; i <= num - 1; i++)
        {
            for (j = i + 1; j <= num; j++)
            {
                sum2 = wine[z] + wine [z-1] + wine[i] + wine[j];
                temp2 = max(temp2, sum2);
            }
        }
    }

    int answer= max(temp1 , temp2);
    cout << answer;

}