#include <iostream>
#include<fstream>
using namespace std;

int main()
{
    float man, woman;
    //ifstream ii("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju_algo_practice\\input.txt");
    ifstream ii("input.txt");
    //ifstream ii("C:\\input.txt");


    //ofstream oo("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju_algo_practice\\output.txt");
    ofstream oo("output.txt");
    //ofstream oo("C:\\output.txt");
    float point, sum = 0, i = 0;
    while (1)
    {
        ii >> man >> woman;
        if (man == 999 && woman == 999)
        {
            break;
        }
        if (man > woman)
        {
            point = man;
        }
        else
        {
            point = woman;
        }
        sum = sum + point;
        i++;
    }

    oo << sum / i;


    ii.close();
    oo.close();

    return 0;
}