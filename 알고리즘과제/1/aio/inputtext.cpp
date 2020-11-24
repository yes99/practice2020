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
    int n;
    cout << "how many programs : ";
    cin >> n;

    for (i = 0; i < n; i++)
    {
        cout << "input the name of the text file, make sure include .txt : ";
        cin >> text;
        ifstream ii(text);
        while (getline(ii, temp))
        {
            code[i] = code[i] + temp;
        }
        cout << code[i]<<endl;;
        ii.close();
    }
    return 0;
}


void inputtext()
{
        string code[10];
    int i, j, k;
    string temp;
    string text;
    string num;
    int n;
    cout << "how many programs : ";
    cin >> n;

    for (i = 0; i < n; i++)
    {
        cout << "input the name of the text file, make sure include .txt : ";
        cin >> text;
        ifstream ii(text);
        while (getline(ii, temp))
        {
            code[i] = code[i] + temp;
        }
        cout << code[i]<<endl;;
        ii.close();
    }
}