#include<iostream>
using namespace std;

long long five(long long n)
{
    long long result = 0;
    for (long long i = 5; i <= n; i *= 5)
        result += n / i;
    return result;
}
long long two(long long n)
{
    long long result = 0;
    for (long long i = 2; i <= n; i *= 2)
        result += n / i;
    return result;
}
int main()
{
    long long N, M;
    cin >> N >> M;

    cout << min(five(N) - (five(M) + five(N - M)), two(N) - (two(M) + two(N - M)));

}