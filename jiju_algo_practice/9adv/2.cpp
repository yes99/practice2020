#include <iostream>
#include<fstream>
#include <string>
using namespace std;
//ii >> 
//oo <<
int main()
{

//ifstream ii("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju\\input.txt");
ifstream ii("input.txt");


//ofstream oo("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju\\output.txt");
ofstream oo("output.txt");
int answer = 4;
oo<< answer;


ii.close();
oo.close();
return 0;
}