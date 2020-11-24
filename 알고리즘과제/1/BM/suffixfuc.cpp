#include <iostream>
#include <string>
using namespace std;

int suffix(string pattern, int a)
{
    int i, j;
    int l = pattern.length();
    int suf = -1;
    int check;
    for (j = 0; j < a+1; j++)
    {
        //for (i = 0; i < j + 1; i++)
        for (i = 0; i < (l / 2); i++)
        {
            check = l - j + i - 1;

            if (j > l / 2)
            {
                break;
            }
            else if (pattern[i] == pattern[check])
            {
                suf = i;
            }
            else
            {
                break;
            }
        }
    }
    return suf;
}


int main()
{
    int i;
    string a = "ASTRACASTRA";
    for (i = 0; i < a.length(); i++)
    {
        cout << suffix(a, i) << endl;
    }
}
