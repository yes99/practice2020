#include <iostream>
#include<fstream>
#include<string>
#include<math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
    string find;
    string change;
    string sentence;

    ifstream ii("D:\\input.txt");
    //ifstream ii("input.txt");
    ofstream oo("D:\\output.txt");
    //ofstream oo("output.txt");

    getline(ii, find);
    getline(ii, change);
    getline(ii, sentence);
    int i, j;
    int checknum = find.length();
    int standard;
    for (i = 0; i <= sentence.length() - checknum; i++)
    {
        for (j = 0; j < checknum; j++)
        {
            if (find[j] != sentence[i + j])
            {
                break;
            }
        
        }
        if (j == checknum)
        {
            standard = i; //몇번째 항부터 apple 가 시작인지
        }
    } // 브루트 포스 알고리즘
    

    //sentence.erase(standard, find.length());

    sentence.replace(standard, change.length(), change);

    oo << sentence;



    ii.close();
    oo.close();
    return 0;
}


