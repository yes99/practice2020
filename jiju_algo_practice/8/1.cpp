#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{

    int start, hop, obstacle;
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");
    ii >> start >> hop >> obstacle;
    int i = 0;
    for(i = start ; i <= obstacle ; i = i + hop)
    {

    }
    oo << i;

    ii.close();
    oo.close();
    return 0;
}