#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int N, M, K;

    cin >> N >> M >> K;

    int ans = 0;
    int total = N + M - K;

    while (N > 1 && M > 0 && total > 2)
    {
        N -= 2;
        M -= 1;
        total -= 3;
        ans++;
    }

    cout << ans;

    return 0;
}