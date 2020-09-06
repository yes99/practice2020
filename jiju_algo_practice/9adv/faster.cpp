#include <iostream>
#include<fstream>
#include <string>
using namespace std;
//ii >> 
//oo <<
int main()
{
    string input1, input2;
    string answer;
    //ifstream ii("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju\\input.txt");
    ifstream ii("input.txt");


    //ofstream oo("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju\\output.txt");
    ofstream oo("output.txt");
    ii >> input1 >> input2;
    char a, b,c;
    

    ii.close();
    oo.close();
    return 0;
}