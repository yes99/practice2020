#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
    int flee, day;
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");
    ii >> flee >> day;
    int i;
    int answer = 0;
    for ( i = 1 ; i < day+2 ; i++)
    {
        answer = answer + i;
    }
    oo << flee + answer;

    ii.close();
    oo.close();
    return 0;
}