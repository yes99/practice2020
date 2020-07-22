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
    
    int point; 
    point = (n+1)/2;
    if (point % 2 == 1)
    {
        oo << 1;
    }
    else
    {
        oo << point / 2 +1;
    }
    


    ii.close();
    oo.close();
    return 0;
}