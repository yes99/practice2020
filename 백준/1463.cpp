#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;
//ii >>
//oo <<
int main()
{

    int num;
    int flag1 = 0, flag2 = 0;
    int cnt = 0;
    while (1)
    {
        if(log3(num) - int(log3(num))  )



        if (num % 3 == 0)
        {
            num = num / 3;
            cnt++;
        }
        else
        {
            flag1 = 22;
        }

        if (num % 2 == 0)
        {
            num = num / 3;
            cnt++;
        }
        else
        {
            flag2 = 22;
        }
        
        if (flag1 == 22 && flag2 == 22)
        {
            num = num - 1;
            cnt++;
        }
        
        if(num == 1)
        {
            break;
        }
    }

    return 0;
}