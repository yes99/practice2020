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
    int time = (-n);
    for(int i = 0; i < 33 ; i++)
    {
        time = time + n;
        oo << time / 3600 << " " << (time % 3600)/60 << " " << time%60 << endl;  
    }

    ii.close();
    oo.close();
    return 0;
}