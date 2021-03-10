#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int k;
    cin >> k;
    int b;
    cin >> b;
    vector <int> v;
    vector <char> o;
    while(k!=0)
    {
        o.push_back(k%b);
        k = k/b;
    }

//A~Z :::: 65~90    
    for(int i = 0 ; i < o.size();i++)
    {
        if(o[i]>9)
        {
            char alpha;
            alpha = o[i] + 55;
            o[i] = alpha;
        }
        else
        {
            int num;
            //0~9  48 57
            num = o[i]+ 48;
            o[i] = num;
        }
    }
    reverse(o.begin(), o.end());

    for(int i = 0 ; i < o.size();i++)
    {
        cout<<o[i];
    }

}