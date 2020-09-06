#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
    int num;
    double distance;
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");
    int i = 0;
    double finaldis, temp=10000000;
    int output;
    ii >> num;
    while(i < num)
    {
        ii >> distance;
        double go = 0;
        while(go < 1000)
        {
            go = go + distance;
        }
        finaldis = go - 100;
        if(finaldis < temp)
        {
            output = i+1;
            temp = finaldis;
        }
        i++;
    }
    oo << output;

    ii.close();
    oo.close();
    return 0;
}

