#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
    int i, j ,k;
    int check, x;
    string text = "gcatcgcagagagtataca";
    string pattern = "ababa";
    char Parray[100];
    int fail[100];
    fail[1] = 0;
    fail[2] = 1;

    for(i = 1 ; i <pattern.length()+1; i ++)
    {
        Parray[i] = pattern[i-1];
    }
    for(i = 1 ; i <pattern.length()+1; i ++)
    {
        cout<<Parray[i];
    }
    cout<<endl;
    //flow chart 작성 시작 
    for(i = 3; i <pattern.length()+1; i ++)
    {
        if(Parray[i-1]==Parray[fail[i-1]])
        {
            fail[i]= fail[i-1]+1;
        }
        else
        {
            check = i;
            if(fail[fail[i-1]]==0)
            {
                fail[i] = 1;
            }
            else
           { 
               x = fail[check-1];
               do
                {
                    if(fail[x] ==0)
                    {
                        fail[check] = 1;
                        break;
                    }
                    else if (Parray[fail[x]] == Parray[i-1])
                    {
                        fail[check] = Parray[i-1]+1;
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
    for(i = 2 ; i <pattern.length()+1; i ++)
    {
        if(Parray[i]== Parray[1])
        {
            fail[i] = 0;
        }
    }
    for(i = 1 ; i <pattern.length()+1; i ++)
    {
        cout<<fail[i]<<" ";
    }
    //플로우 차트 그리기 완료
}
