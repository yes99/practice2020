#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
    int num, input;
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");
    ii >> num;

    int root;
    int origin;
    int largeroot = 0;
    int largeorigin = 0;
    int temp = 0;

    for (int i = 0; i < num; i++)
    {
        root = 0;
        ii >> input;
        origin = input;
        while (input > 0)
        {
            root = root + input % 10;
            input = input / 10;
        }  // 한바퀴 돌리자
        while (1) 
        {
            if (root >= 10)
            {
                temp = temp + root % 10;
                root = root / 10;
            } // 만약 10보다 크면 한번 더 쪼개주고
            else
            {
                break;
            } // 아니면 재끼자
        }
        if (temp != 0)
        {
            root = temp;
        } // 우리가 쓴 템프, 이게 0이면 건들지 않은거고 0이 아니면 한번더 쪼갰다는 작업

        if (root > largeroot)
        {
            largeroot = root;
            largeorigin = origin;
        }
        if (root == largeroot)
        {
            if (origin < largeorigin)
            {
                largeorigin = origin;
            }
        }
    }
    oo << largeorigin;

    ii.close();
    oo.close();
    return 0;
}