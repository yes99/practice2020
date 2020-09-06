#include <iostream>
#include<fstream>
using namespace std;

int main()
{
    int n, length;
    //ifstream ii("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju_algo_practice\\input.txt");
    ifstream ii("input.txt");
    //ifstream ii("C:\\input.txt");


    //ofstream oo("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju_algo_practice\\output.txt");
    ofstream oo("output.txt");
    //ofstream oo("C:\\output.txt");
    
    ii >> n;
    int i = 0, cnt = 0;
    while (i < n)
    {
        ii >> length;
        if (length > 5)
        {
            cnt++;
        }
        i++;
    }
    
    oo << cnt + 100;


    ii.close();
    oo.close();
    
    return 0;
}