#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
    double start, hop, end;
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");
    ii >> start >> hop >> end;
    double i = 0;
    for(i = start ; i <= end ; i = i+hop)
    {
        double answer = int(i *10 +0.5)/10.0;
        cout.setf(ios::fixed);
        cout.precision(1);
        oo << answer << endl;
        
    }


    ii.close();
    oo.close();
    return 0;
}
/*
double temp = cnt / double (dataNum) * 100; // 퍼센트
double ave = int(temp * 10 + 0.5) / 10.0;// 반올림과정
cout.setf(ios::fixed);
cout.precision(1);
*/