#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
    int i, j, k;
    int check, x;
    string text = "gcatcgcagagagtatacagcagagaggcagagag";
    string pattern = "gcagagag";
    char Parray[100];
    int fail[100];
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
    //flow chart �ۼ� ���� 
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

    for (i = 1; i < pattern.length() + 1; i++)
    {
        cout << fail[i] << " ";
    }//�÷ο� ��Ʈ �׸��� �Ϸ�

    //kmp ����
    int origin, move;
    j = 0;
    int cnt;
    for (i = 0; i < text.length(); i++)
    {
        cnt = 1;
        origin = i;
        for (j = 0; j < pattern.length(); j++)
        {
            if (text[i + j] == pattern[j])
            {
                cnt++;
            }
            else
            {
                break;
            }
        }
        if (cnt == pattern.length()+1)
        {
            printf("\nfind at %d\n", i);
        }
        else
        {
            //�ٽɱ���
            move = cnt - fail[cnt];
            i = i + move-1;
        }
    }
}
