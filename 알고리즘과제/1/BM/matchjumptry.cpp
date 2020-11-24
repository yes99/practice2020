#include <iostream>
#include <string>
using namespace std;

int matchjump(string text, string pattern)
{
    int found = -1;
    int answer;
    int save1;
    int save2;
    do
    {
        found = text.find(pattern, found + 1);
        if (found != -1) //찾긴 찾음?
        {
            //if(text[found-1]!= )
        }

    } while (found != -1);
    return answer;
}
// void putword(string pattern, char parray[])
// {
//     int i;
//     for (i = 1; i < pattern.length() + 1; i++)
//     {
//         parray[i] = pattern[i - 1];
//     }
//     return parray;
// }

int main()
{
    // 검색 대상 문자열
    string t = "ABCABCABCABCABC";
    // 어떤 문자들을 찾아볼 것인가?,2
    string p = "GCAGAGAG";
    int ln;
    int i;
    char parray[100];
    char mj[100];
    int m =p.length(); //6
    int r;

    //옮기기
    for(i = 1 ; i <m+1;i++)
    {
        parray[i] = p[i-1];
    }
    cout << endl;
    string tempt;
    string tempp;
    mj[m] = 1;
    for(i=m-1;i>0;i--) // 자 돌릴게요...
    {
        tempt = p.substr(0, i);
        tempp = p.substr(i,m);

        cout << i << " position wrong p["<< i << "] " <<tempt << " "<<tempp<<" ";
        r = matchjump(tempt, tempp);
        cout <<r << endl;
        
    }
    
    //ln = matchjump(t, p);
    //cout << "last time is " << ln;
}