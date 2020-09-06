#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
    int n, x, time, a;
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");
    ii >> n >> x >> time;
    int cnt = 0;
    int total = 0;
    for(int i = 0; i < time; i++)
    {
        ii >> a;
        cnt = cnt + x +1 - a;
        total = total + x+1;
        if(total == n-1)
        {
            oo << cnt;
            break;
        }
    }


    ii.close();
    oo.close();
    return 0;
}