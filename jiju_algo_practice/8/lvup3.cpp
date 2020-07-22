#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
    int num;
    int width, length, height;
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");
    ii >> num;
    int total = 0;
    int amount;
    for(int i = 0 ; i < num ; i++)
    {
        ii >> width >> length >> height;
        amount = (width/0.25) * (length/0.25) * (height/0.25);
        total = total + amount;
    }
    oo << total;
    ii.close();
    oo.close();
    return 0;
}