#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
    int first, num, change;
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");
    ii >> first >> num;
    for(int i = 0; i < num ; i++)
    {
        ii >> change;
        first = first + change;
    }
    oo << first;
    ii.close();
    oo.close();
    return 0;
}