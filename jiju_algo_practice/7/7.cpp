#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// ii >>
// oo <<
int main()
{
    int hz, run, time;
    int num;
    int enemy, enemytime;
    //ifstream ii("C:\\이현석\\input.txt");
    ifstream ii("input.txt");

    //ofstream oo("C:\\이현석\\output.txt");
    ofstream oo("output.txt");
    ii >> hz >> run >> time;
    ii >> num;
    int answer = 0;
    int cnt = 0;
    int i;
    for (i = 0; i < num; i++)
    {
        ii >> enemy >> enemytime;
        if (enemy % hz == 0 && enemytime > run)
        {
            cnt++;
        }
        answer = answer + enemytime;
        if (cnt == time)
        {
            oo << answer;
            break;
        }
    }
    if (cnt != time)
    {
        oo << "0";
    }
    else if (enemytime > run && cnt!=time)
    {
        oo << answer;
    }

    ii.close();
    oo.close();
    return 0;
}