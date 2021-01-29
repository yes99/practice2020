#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

bool comp(int a, int b)
{
    return a < b;
}

int main()
{

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    scanf("%d", &n);
    //cin >> n;
    int want;
    cin >> want;
    scanf("%d", &want);

    int num[5000000];
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
        scanf("%d", num[i]);
    }

    stable_sort(num, num + n, comp);

    cout << num[want - 1];
}
