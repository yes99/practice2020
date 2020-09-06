#include <iostream>
#include<fstream>
using namespace std;

int main()
{
int n, cnt, cNum, gNum;
float cAve, gTot;
//ifstream ii("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju\\input.txt");
ifstream ii("input.txt");
//ifstream ii("C:\\input.txt");


//ofstream oo("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju\\output.txt");
ofstream oo("output.txt");
//ofstream oo("C:\\output.txt");

cnt = 0;
gNum = 0;
gTot = 0;
ii >> n;
do
{
    cnt ++;
    ii >> cNum >> cAve;
    gNum += cNum;
    gTot += cNum *cAve;
} while (cnt < n);


oo << gTot / gNum;


ii.close();
oo.close();
return 0;
}