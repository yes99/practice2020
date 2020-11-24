#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
void flowchart(string pattern, int fail[])
{
    int i;
    char Parray[100];
    int check, x;
    fail[1] = 0;
    fail[2] = 1;

    for (i = 1; i < pattern.length() + 1; i++)
    {
        Parray[i] = pattern[i - 1];
    }
    for (i = 1; i < pattern.length() + 1; i++)
    {
        cout << Parray[i];
    }
    cout << endl;
    //flow chart 작성 시작 
    for (i = 3; i < pattern.length() + 1; i++)
    {
        if (Parray[i - 1] == Parray[fail[i - 1]])
        {
            fail[i] = fail[i - 1] + 1;
        }
        else
        {
            check = i;
            if (fail[fail[i - 1]] == 0)
            {
                fail[i] = 1;
            }
            else
            {
                x = fail[check - 1];
                do
                {
                    if (fail[x] == 0)
                    {
                        fail[check] = 1;
                        break;
                    }
                    else if (Parray[fail[x]] == Parray[i - 1])
                    {
                        fail[check] = Parray[i - 1] + 1;
                        break;
                    }
                    else
                    {
                        x = fail[x];
                    }
                } while (1);
            }
        }
    }
}

void kmpmove(string text, string pattern, int fail[])
{
    int move;
    int i, j;
    int cnt;
    for (i = 0; i < text.length(); i++)
    {
        cout << "now you are at " << i << "   ";
        cnt = 1;
        for (j = 0; j < pattern.length(); j++)
        {
            if (text[i + j] == pattern[j])
            {
                cnt++;
            }
            else
            {
                cout << "miss match at " << i + j << endl;
                break;
            }
        }
        if (cnt == pattern.length() + 1)
        {
            printf("\nfind at %d\n", i);
            move = cnt - fail[cnt - 1];
            i = i + move - 1;
        }
        else
        {
            //핵심구간
            move = cnt - fail[cnt];
            i = i + move - 1;
        }
    }
}

int main()
{
    int i, j, k;

    string text = "gcatcgcagagagtatacagcagagaggcagagag";                             //"abababacabababcacaabbc";
    string pattern = "gcagagag";                      //"abababca";   
    int fail[100];

    flowchart(pattern, fail);
    for (i = 1; i < pattern.length() + 1; i++)
    {
        cout << fail[i] << " ";
    }//플로우 차트 그리기 완료
    cout << endl;
    //kmp 시작
    kmpmove(text, pattern, fail);
}
