#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
    int r, n;
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");
    ii >> r>> n;
    int answer=1;
    for(int i = 0; i<n; i++)
    {
        answer = answer * r;
    }
    oo << answer;
    ii.close();
    oo.close();
    return 0;
}