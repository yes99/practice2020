#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
    int n;
    //ifstream ii("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju\\input.txt");
    ifstream ii("input.txt");

    //ofstream oo("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju\\output.txt");
    ofstream oo("output.txt");
    ii>>n;
    int answer;
    answer = n*(n+1)*(2*n+1)/6 - n*(n+1)/2 + 3*n;

    oo << answer;


    ii.close();
    oo.close();
    return 0;
}