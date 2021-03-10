#include <iostream>
using namespace std;

int main()
{
    int a, b;
    int g;
    int num;
    int i, j, k;
    cin >> num;
    for (j = 0; j < num; j++)
    {
        cin >> a >> b;
        for (i = a; i > 0; i--)
        {
            if (a % i == 0 && b % i == 0)
            {
                g = i;
                break;
            }
        }
        cout << a * b / g;
    }
}