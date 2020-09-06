#include <iostream>
#include<fstream>
using namespace std;

int main()
{
    float man, woman;
    //ifstream ii("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju_algo_practice\\input.txt");
    //ifstream ii("input.txt");
    //ifstream ii("C:\\input.txt");


    //ofstream oo("C:\\Users\\lhyun\\OneDrive\\바탕 화면\\practice2020\\jiju_algo_practice\\output.txt");
    //ofstream oo("output.txt");
    //ofstream oo("C:\\output.txt");
    float tempert;
    int number, day=0, cnt=0;
    cin >> number;
    while (cnt<4)
    {
       cin >> day >> tempert;
       if(tempert > 15)
       {
           cnt++;
       }
       else
       {
            cnt = 0;
       }
       day++;
    }

    cout<< day;


//    ii.close();
//    oo.close();

    return 0;
}