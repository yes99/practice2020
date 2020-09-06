#include <iostream>
#include <fstream>
using namespace std;
//ii>>
//oo<<
int main()
{
    int cobracode, day;
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");

    int i = 0;
    int first = 0, second = 0;
    int firstoutput=0, secondoutput;
    while (i < 5)
    {
        ii >> cobracode >> day;
        if (day >= first)
        {
            second = first;
            secondoutput = firstoutput;
            firstoutput = cobracode;
            first = day;
        }
        if (day < first && day > second)
        {
            secondoutput = cobracode;
            second = day;
        }
        i++;
    }
    int t;
    if(firstoutput > secondoutput)
   {
       t = firstoutput;
       firstoutput = secondoutput;
       secondoutput = t;
   }
    oo << firstoutput << endl;
    oo << secondoutput << endl;

    ii.close();
    oo.close();
    return 0;
}