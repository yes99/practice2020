#include <iostream>
#include <vector>

using namespace std;

long long GCD(long long a, long long b)
{
    if (a % b == 0)
    {
        return b;
    }
    return GCD(b, a % b);
}

int main()
{
    int n, num, number;
    cin >> n;
    int i, j, k;
    vector<long long> a;
    vector<long long> b;
    for (i = 0; i < n; i++)
    {
        cin >> num;
        for (j = 0; j < num; j++)
        {
            cin >> number;
            a.push_back(number);
        }

        for(j = 0 ; j < num ; j++)
        {
            for(k = j+1 ; k<num; k++)
            {
                b.push_back(GCD(a[j], a[k]));
            }
        }
        long long sum = 0;
        /*for(j = 0 ; j < b.size(); j++)
        {
            cout << b[j]<< " ";
        }
        cout<<endl;
    */
        for(j = 0 ; j < b.size() ; j++)
        {
            sum = sum + b[j];
        }
        cout << sum<<"\n";
        a.resize(0);
        b.resize(0);
    }
}