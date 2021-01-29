#include <iostream>
using namespace std;

int main()
{
    int n;
    //int f1, f2;
    int i;
    int answer[1001];
    int input;
    cin >> n;
    answer[0] = 0;
    answer[1] = 1;
    answer[2] = 3;
    answer[3] = 5;

    for (i = 4; i <= n; i++)
    {
        input = answer[i-1] + 2 * answer[i-2];
        answer[i] = input % 10007;
    }

    cout << answer[n];
}