#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
    string whole;
    int i, j, k;
    ifstream ii("D:\\input.txt");
    //ifstream ii("C:\Users\lhyun\OneDrive\Desktop\practice2020\알고리즘과제\2\inputappendtab.txt");

    ofstream oo("D:\\이현석\\output.txt");
    //ofstream oo("output.txt");

    for (i = 0; i < 3; i++)
    {
        getline(ii, whole);
        cout << "한번 완료" << endl;
        cout << whole << endl;
    }

    ii.close();
    oo.close();
    return 0;
}