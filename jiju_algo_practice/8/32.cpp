#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
    int right, up, start, dir;
    //ifstream ii("input.txt");
    ifstream ii("D:\\input.txt");

    //ofstream oo("output.txt");
    ofstream oo("D:\\output.txt");
    ii >> right >> up >> start >> dir;

    int x = start, y;
    int a = start;
    int temp;
    int way = dir;
    while (1)
    {
        do
        {
            y = dir * x + a;
            x = x + way;
        } while (x > 0 && x < right && y < up);

        if (dir > 0 || dir < 0)
        {
            a = right + a;
            way = -1 * dir;
            dir = -1 * dir;
        }
        else if (y == up)
        {
            temp = up - a;
            a = up + temp;
        }

        if (y == 0)
        {
            oo << x ;
            break;
        }
    }

    ii.close();
    oo.close();
    return 0;
}