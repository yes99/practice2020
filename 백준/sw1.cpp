#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;
//ii >>
//oo <<
int main()
{
    int lcnt =0; 
    int rcnt =0;

    string world;

    cin>>world;

    int i, j ,k;

    for(i = 0; i<world.length();i++)
    {
        if(world[i] == '(')
        {
            lcnt++;
        }
        else
        {
            rcnt++;
        }
    }

    if(rcnt == lcnt)
    {
        cout<<"YES";
    }
    else
    {
        cout<<"NO";
    }


}