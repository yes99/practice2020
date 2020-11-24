#include <iostream>
#include <string>
using namespace std;

int suffix(string pattern, int a)
{
    int i, j;
    int l = pattern.length();
    int suf = -1;
    int check;
    for (j = 0; j < a + 1; j++)
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
    return suf + 1;
}

int matchjump(string pattern, string part, int i, string originpattern)
{
    int found = -1;
    int answer;
    int save1 = -100;
    int save2 = -100;
    int m = originpattern.length();
    int q = suffix(originpattern, i);
    cout << "suffix is " << q << " ";
    do
    {
        found = pattern.find(part, found + 1);
        if (found != -1) //찾긴 찾음?
        {
            if (pattern[found - 1] != pattern[i])
            {
                save1 = found;
            }
            else
            {
                save2 = found;
            }
        }
    } while (found != -1);

    if (save1 == -100 && save2 != -100)
    {
        answer = m - save2 + m + q;
    }
    else
    {
        answer = m - save1 + 1;
    }
    return answer;
}

int main()
{
    // 검색 대상 문자열
    //string t = "ABCABCABCABCABC";
    // 어떤 문자들을 찾아볼 것인가?,2
    string p = "GCAGAGAG";
    int ln;
    int i;
    char parray[100];
    int mj[100];
    int m = p.length(); //6
    int matchjumpnum;

    //옮기기
    for (i = 1; i < m + 1; i++)
    {
        parray[i] = p[i - 1];
    }
    cout << endl;
    string temppattern;
    string temppart;
    mj[m] = 1;
    for (i = m - 1; i > 0; i--) // 자 돌릴게요...
    {
        temppattern = p.substr(0, i);
        temppart = p.substr(i, m);

        cout << i << " position wrong p[" << i << "] " << temppattern << " " << temppart << " ";
        matchjumpnum = matchjump(temppattern, temppart, i, p);
        mj[i] = matchjumpnum;
        cout << endl;
    }
    cout << endl;
    for (i = 1; i < m + 1; i++)
    {
        cout << mj[i] << " ";
    }
    //ln = matchjump(t, p);
    //cout << "last time is " << ln;
}