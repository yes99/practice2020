#include <iostream>
#include <math.h>

using namespace std;

int prime(int num)
{
    int i, j;
    int check = 0;
    if(num ==1)
    {
        return 1;
    }
    for (i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
        {
            check = 1;
            break;
        }
    }
    if (check == 1)
    {

        //cout << " nono" << endl;
        return 1;
    }
    else
    {
        //cout << num << "is prime" << endl;
        return 0;
    }
}

int main()
{
    int n , m;
    int num[10000];
    cin >>m >> n;
    int cnt[10000];
    int count = 0;
    int i, j;
    int z=0;
    for (i = m; i <= n; i++)
    {
        if(prime(i) == 0)
        {
            cnt[z]=i;
            z++;
        }
    }
    for (i = 0; i <z; i++)
    {
        cout << cnt[i] << "\n";
    }
    return 0;
}