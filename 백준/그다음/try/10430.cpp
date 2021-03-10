#include <iostream>
using namespace std;

int main()
{
    int a, b,c;
    int a1,a2,a3,a4;
    cin >> a>>b>>c;
    a1 = (a+b)%c;
    a2 = ((a%c)+(b%c))%c;
    a3 = (a*b)%c;
    a4 = ((a%c)*(b%c))%c;
    cout<<a1<<"\n"<<a2<<"\n"<<a3<<"\n"<<a4<<"\n";

}