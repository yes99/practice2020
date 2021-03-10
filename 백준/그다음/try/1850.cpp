#include <iostream>
#include <string>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    int a, b;
    cin>>a>>b;

    int g;

    while(b != 0)
    {
        g = a%b;
        //cout<<g<<endl;
        a=b;
        b=g;
    }

    //cout<<endl << a<<endl;

    int i , j;
    //string one = "";
    for(i =0 ; i <a; i++)
    {
        cout<<1;
    }

}