#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
    int standard, cnt, data;
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");


    ii>>standard >> cnt;
    int i = 0;
    int sub;
    int answer=10000000;
    int output;
    while(i < cnt)
    {
        ii>> data;
        sub = standard - data;
        if (sub <0)
        {
            sub = sub * (-1);
        }
        if(sub < answer)
        {
            answer = sub;
            output = data;
        }
        if(sub == answer)
        {
            if(data < output)
            {
                output = data;
            }
        }
        i++;
    }   
    oo<< output;
    ii.close();
    oo.close();
    return 0;
}