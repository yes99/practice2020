#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
    int num;
    int start, end, kg;
    ifstream ii("input.txt");
    //ifstream ii("D:\\input.txt");

    ofstream oo("output.txt");
    //ofstream oo("D:\\output.txt");
    ii >> num;
    int sub;
    int answer = 0;
    int energy;
    int submul;
    for(int i = 0 ; i < num; i++)
    {
        ii >> start >> end >> kg;
        sub = end - start;
        if(sub < 0)
        {
            submul = -1* sub;
            energy = 1 * submul + 10 * kg * submul;
        }
        else
        {
            energy = 5  * sub + 50 * kg * sub;
        }
        answer = answer + energy;
    }
    
    oo << answer;

    ii.close();
    oo.close();
    return 0;
}