#include <iostream>
#include<fstream>
using namespace std;

int main()
{
int n, length;
ifstream ii("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju\\input.txt");
//ifstream ii("input.txt");
//ifstream ii("C:\\input.txt");


ofstream oo("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju\\output.txt");
//ofstream oo("output.txt");
//ofstream oo("C:\\output.txt");
ii.close();
oo.close();
ii >> n;
int i = 0, cnt = 0;
while (i < n)
{
    ii >> length;
    if (length > 5);
    cnt++;
}
cout << cnt;

//oo << cnt + 100;


//ii.close();
//oo.close();
return 0;
}