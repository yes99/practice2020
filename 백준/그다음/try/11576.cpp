#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    int a, b, m , t[100];

    cin >> a >>b >>m;

    int i , j ,k;
    int dec = 0;
    for(i = 0 ; i < m ; i++)
    {
        cin >> t[i];
        dec = dec +  t[i] * pow(a , m-i-1);   
        cout << dec << " ";
    }

    cout << dec;
}