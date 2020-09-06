#include <iostream>
#include <fstream>
using namespace std;
//ii>>
//oo<<
int main()
{
    int a,b, time;
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");
    int i = 0;
    int a1 , a2;
    ii >> a>> b >>time;
    while (i < time)
    {
      if(a * i % 100 + b * i % 140 == 140 && a * i % 100 >=0 || a * i % 100 <11)
      {
          oo << i << endl;
      }
      else if(a * i % 100 + b * i % 140 == 100 && b * i % 140 >=0 || b * i % 140 <11)
      {
          oo << i << endl;
      }
      i++;
    /*
      else if(a * i % 100 ==1 && b * i % 140 == 139)
      {
          
      }
      else if(a * i % 100 ==2 && b * i % 140 == 138)
      {
          
      }
      else if(a * i % 100 ==3 && b * i % 140 == 137)
      {
          
      }
      else if(a * i % 100 ==0 && b * i % 140 == 0)
      {
          
      }
      else if(a * i % 100 ==0 && b * i % 140 == 0)
      {
          
      }
      else if(a * i % 100 ==0 && b * i % 140 == 0)
      {
          
      }
      else if(a * i % 100 ==0 && b * i % 140 == 0)
      {
          
      }
      else if(a * i % 100 ==0 && b * i % 140 == 0)
      {
          
      }
      else if(a * i % 100 ==0 && b * i % 140 == 0)
      {
          
      }
      else if(a * i % 100 ==0 && b * i % 140 == 0)
      {
          
      }
      else if(a * i % 100 ==0 && b * i % 140 == 0)
      {
          
      }
*/

    }

    ii.close();
    oo.close();
    return 0;
}