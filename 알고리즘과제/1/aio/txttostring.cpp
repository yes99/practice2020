#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
    string code[10];
    int i, j, k;
    string temp;
    string text;
    string num;
    for (i = 0; i < 5; i++)
    {
        text = "input";
        num = to_string(i);
        text.append(num);
        text.append(".txt");
        cout << text << endl;
        ifstream ii(text);
        while(getline(ii, temp))
        {
            code[i] = code[i] + temp;
        }

        cout << "text[" << i << "] :" << code[i] << endl;
        ii.close();
    }

    return 0;
}


void txttostring(string code[])
{
    int i, j, k;
    string temp;
    string text;
    string num;
    for (i = 0; i < 5; i++)
    {
        text = "input";
        num = to_string(i);
        text.append(num);
        text.append(".txt");
        cout << text << endl;
        ifstream ii(text);
        while(getline(ii, temp))
        {
            code[i] = code[i] + temp;
        }

        cout << "text[" << i << "] :" << code[i] << endl;
        ii.close();
    }

}