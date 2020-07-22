#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{

    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");
    double temp;
    double ave = int(temp * 10 + 0.5) / 10.0;// 반올림과정
    cout.setf(ios::fixed);
    cout.precision(1);

    ii.close();
    oo.close();
    return 0;
}