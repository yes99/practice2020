#include <iostream>
#include <stack>
#include <list>
using namespace std;

int main()
{
    string word;
    cin >> word;
    stack<int>s;
    int i, j , k;

    for(i=0;i<word.length();i++)
    {
        s.push(word[i]);
    }
    int num;
    cin>>num;
    char order;
    int plus;
    list<int> temp;

    for(i=0; i <num;i++)
    {
        cin>>order;
        if(order=='L')
        {
            temp.push_back(s.top());
            s.pop();
        }
        else if(order =='D')
        {
            s.push(temp.front());
            temp.pop_front();
        }
        else if(order =='B')
        {
            s.pop();
        }
        else if(order =='P')
        {
            cin>>plus;
            s.push(plus);
        }
    }

    for(i=0;i<temp.size();i++)
    {
        s.push(temp.front());
        temp.pop_front();
    }

    while(!s.empty())
    {
        cout<<s.top();
        s.pop();
    }
}