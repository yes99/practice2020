#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
    int n;
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");
    ii >> n;
    int fac = 1;
    int point = n;
    for(int i = 0 ; i < n ; i++)
    {
        fac = fac * point;
        point--;
    }
    oo << fac;
    ii.close();
    oo.close();
    return 0;
}