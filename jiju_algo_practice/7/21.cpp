#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{

    int f, s, t;
    int total;
    int inputmoney;
    int pull;

    //ifstream ii("input.txt");
    ifstream ii("D:\\input.txt");

    //ofstream oo("output.txt");
    ofstream oo("D:\\output.txt");
    
    ii>>f>>s>>t >>total >> inputmoney >> pull;
    int origin = inputmoney;
    for(int i = 0 ; i <pull ; i++)
    {
        inputmoney = inputmoney - 10;
        total = total + 10;
        f= (((f * 1234)+8) * ((f * 1234)+8) -7) % 10;
        s= (((s * 1234)+8) * ((s * 1234)+8) -7) % 10;
        t= (((t * 1234)+8) * ((t * 1234)+8) -7) % 10;
        if(f == s == t)
        {
            inputmoney = inputmoney + total/2;
            total = total/2;
            if(inputmoney % 10 != 0)
            {
               //반올림
               inputmoney= (inputmoney +5) / 10 * 10;
            }
        }
        if(inputmoney == 0)
        {
            break;
        }   
    }

    oo << inputmoney << " " << origin - inputmoney;

    ii.close();
    oo.close();
    return 0;




}