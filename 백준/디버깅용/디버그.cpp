#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n;
    string g;
    int i, j, k;
    cin >> n;
    int cnt1, cnt2;
    int answer[1000000];
    for (i = 0; i < n; i++)
    {
        cnt1 = 0;
        cnt2 = 0;
        cin >> g;
        for (j = 0; j < g.length(); j++)
        {
            if (g[j] == '(')
            {
                cnt1++;
            }
            else if (g[j] == ')')
            {
                cnt2++;
            }
        }
        if (cnt1 == cnt2)
        {
            answer[i] = 1;
        }
        else
        {
            answer[i] = 0;
        }
    }

    for (i = 0; i < n; i++)
    {
        if (answer[i] == 1)
        {
            cout << "YES" << "\n";
        }
        else
        {
            cout << "NO" << "\n";
        }

    }
}