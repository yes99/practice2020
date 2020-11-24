#include <iostream>
#include <string>
using namespace std;


int main()
{
    string pattern = "ABAB";
    int i, j;
    int l = pattern.length();
    int suf=-1;
    int check;
    for (j = 0; j < l; j++)
    {
        //for (i = 0; i < j + 1; i++)
        for( i = 0 ; i< (l/2) ; i++)
        {
            check = l - j + i - 1;
            
            if (j> l / 2)
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
        cout << "suffix is " << suf+1 << endl;
    }
}