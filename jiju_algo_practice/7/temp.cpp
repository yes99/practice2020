#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
    int f = 5;
    int s = 4;
    int t = 7;
    int pull = 12;
    for(int i =0; i < pull ; i++)
    {
        f= (((f * 1234)+8) * ((f * 1234)+8) -7) % 10;
        s= (((s * 1234)+8) * ((s * 1234)+8) -7) % 10;
        t= (((t * 1234)+8) * ((t * 1234)+8) -7) % 10;
        cout << f << " " << s << " " << t <<endl;
    }
    return 0;
}