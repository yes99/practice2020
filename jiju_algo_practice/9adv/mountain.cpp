#include <iostream>
#include <fstream>
using namespace std;
//ii>>
//oo<<
int main()
{
    int a ,r;
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");
    double answer;
    ii >> a >>r;
    answer  = a * 1/(1+(0.01*r));
    int output = int (answer) /10 * 10;
    oo << output;
    ii.close();
    oo.close();
    return 0;
}a