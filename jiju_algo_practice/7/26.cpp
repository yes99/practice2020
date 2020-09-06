#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;
//ii >>
//oo <<
int main()
{
    double a,b,c,d,e,f;
    double ys, yc;
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");
    int cnt=0;
    ii>>a>>b>>c>>d>>e>>f;
    double PI = 3.14159265;
    double former, latter = 0;
    for(double i = 0 ; i < 6.4; i += 0.01)
    {
        ys = a * sin(b*i -c);
        yc = d * cos(e*i +f);
        former = latter;
        latter = ys - yc;
        if(former < 0 && latter > 0)
        {
            cnt++;
        }
        else if(former >0 && latter <0)
        {
            cnt++;
        }
    }
    oo<<cnt;
    ii.close();
    oo.close();
    return 0;
}