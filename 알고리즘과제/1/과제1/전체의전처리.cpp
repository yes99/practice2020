#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
    string badcode = "0123456789!@";
    int lcode = 4;
    string codep[100];
    int lbadcode = badcode.length();
    int i, j, k;
    for (i = 0; i < lbadcode - lcode + 1; i++)
    {
        codep[i] = badcode.substr(i, lcode);
    }

    for (i = 0; i < lbadcode - lcode + 1; i++)
    {
        cout << i << " " << codep[i] << endl;
    }
}
