#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    int n , k;
    cin >>n >> k;
    cout<<" <";
    int i;
    int r=k;
    for(i = 0 ; i <= n ; i++)
    {
        cout << r << " ";
        r =(r +k) % n;
    }
    cout << ">";

}