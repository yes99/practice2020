#include <iostream>
using namespace std;

int prime(int num)
{
    int i, j;
    int check = 0;
    if(num ==1)
    {
        return 1;
    }
    for (i = 2; i <= (num + 1) / 2; i++)
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
    int n;
    int num[10000];
    cin >> n;
    int cnt[10000];
    int count = 0;
    int i, j;
    for (i = 0; i < n; i++)
    {
        cin >> num[i];
        if (prime(num[i]) == 0)
        {
            cnt[i] = 1;
        }
    }

    for (i = 0; i < n; i++)
    {
        if (cnt[i] == 1)
        {
            count++;
        }
    }

    cout << count;
}