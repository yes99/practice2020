#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
    int x, y, z;
    //ifstream ii("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju\\input.txt");
    ifstream ii("input.txt");

    //ofstream oo("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju\\output.txt");
    ofstream oo("output.txt");
    int temp;
    ii >> x >> y >> z;
    if(x > y)
    {
        temp = x;
        x = y;
        y = temp;
    }

    if(y <= z)
    {
        oo<<x << " " <<y << " " << z;
    }
    else
    {
        if(x <= z)
        {
            oo<<x << " " <<z << " " << y;
        }
        else
        {
            oo<<z << " " <<x << " " << y;            
        }
        
    }
    


    ii.close();
    oo.close();
    return 0;
}