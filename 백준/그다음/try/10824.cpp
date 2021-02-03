#include <iostream>
#include <string>
using namespace std;

int main()
{
    //대문자 65 89
    //소문지 97 122
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string one, two, three, four;
    cin >> one >> two >> three >> four;
    string first, second;
    first = one + two;
    second = three + four;
    long long hana, dul;
    hana = stoll(first);
    dul = stoll(second);
    cout<<first+second;
    //cout <<first <<endl;
    //cout<<second <<endl;
}