#include <iostream>
#include <fstream>
using namespace std;
//ii>>
//oo<<
int main()
{
    int fly, tail, fur, legs, domestic, horn;
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");
    ii >> fly >>tail >> fur >> legs >> domestic >> horn;
    if(fly == 1)
    {
        oo << 9;
    }
    else
    {
        if(tail == 1)
        {
            if(fur == 1)
            {
                if(legs ==1)
                {
                    if(domestic == 1)
                    {
                        if(horn == 1)
                        {
                            oo<<8;
                        }
                        else
                        {
                            oo<<16;
                        }
                        
                    }
                    else
                    {
                        oo<<28;
                    }
                    
                }
                else
                {
                    {
                        oo << 14;
                    }
                }
                
            }
            else
            {
                oo << 5;
            }
        }
        else
        {
            oo << 0;
        }
        
    }

 
    /*
    if(fly == 1)
    {
        oo << 9;
    }
    if(tail == 0)
    {
        oo<< 0;
    }
    if(fur == 0)
    {
        oo << 5;
    }
    if(legs == 0)
    {
        oo << 14;
    }
    if(domestic == 0)
    {
        oo << 28
    }
    if(horn == 1)
    {
        oo<< 8
    }
    if(horn == 0)
    {
        oo << 16
    }
   */
    ii.close();
    oo.close();
    return 0;
}