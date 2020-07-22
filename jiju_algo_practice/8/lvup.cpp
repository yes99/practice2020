#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
    int plate, rice, soup; // 같이 먹는 스님 수
    int monk, ricep, soupp; //접시
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");
    ii >> plate >> rice >> soup;
    int r, s;
    ricep = plate;
    soupp = 0;
    for(int i = 0; i < plate; i++)
    {
        if(ricep * rice == soupp * soup)
        {
            oo << soup* soupp << " " << ricep << " "<< soupp;
        }
        ricep--;
        soupp++;
    }

    ii.close();
    oo.close();
    return 0;
}