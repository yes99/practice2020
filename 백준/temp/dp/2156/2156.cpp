#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int num;
    int wine[10001];
    int i, j, k,z;
    int amount;
    cin >> num;
    for (i = 1; i <= num; i++)
    {
        cin >> amount;
        wine[i] = amount;
    }

    //case1 첫번째 수 포함
    int can1[10001];
    can1[1] = wine[1];
    int sum1;
    int temp1 = 0;

    for (i = 3; i <= num - 2; i++)
    {
        for (j = i + 1; j <= num - 1; j++)
        {
            for (k = j + 1; k <= num; k++)
            {
                sum1 = wine[i] + wine[j] + wine[k];
                if (j == i + 1 && k == i + 2)
                {
                    sum1 = 0;
                }
                temp1 = max(temp1, sum1);
            }
        }
    }
    temp1 = wine[1] + temp1;
    int can2[10001];
    can2[1] = wine[1]+wine[2];
    int sum2;
    int temp2 = 0;
    for(i = 4 ; i <=num-1;i++)
    {
        for(j=i+1;j<=num;j++)
        {
            sum2 = wine[i]+wine[j];
            temp2 = max(temp2, sum2);
        }
    }
    temp2 = wine[1]+wine[2]+temp2;
    int answer= max(temp1 , temp2);
    cout << answer;

}