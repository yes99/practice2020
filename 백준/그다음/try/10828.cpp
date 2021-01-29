#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
/*
push X: 정수 X를 스택에 넣는 연산이다.
pop: 스택에서 가장 위에 있는 정수를 빼고, 그 수를 출력한다. 만약 스택에 들어있는 정수가 없는 경우에는 -1을 출력한다.
size: 스택에 들어있는 정수의 개수를 출력한다.
empty: 스택이 비어있으면 1, 아니면 0을 출력한다.
top: 스택의 가장 위에 있는 정수를 출력한다. 만약 스택에 들어있는 정수가 없는 경우에는 -1을 출력한다.
*/

int main()
{
    vector<int> stack;
    vector<int> answer;
    string it;
    int i, j ,k;
    int n;
    int num;
    cin>>n;
    for(i=0;i<n;i++)
    {
        cin>>it;
        if(it == "push")
        {
            cin>>num;
            stack.push_back(num);
            answer.push_back(num);
        }
        else if(it== "pop")
        {
            //cout<< stack[stack.size()-1]<<"\n";
            answer.push_back(stack[stack.size()-1]);
            stack.pop_back();
        }
        else if(it == "size")
        {
            //cout<<stack.size()<<"\n";
            answer.push_back(stack.size());
        }
        else if(it == "empty")
        {
            if(stack.size()==0)
            {
                //cout<< 1<<"\n";
                answer.push_back(1);
            }
            else
            {
                //cout<<0<<"\n";
                answer.push_back(0);

            }
            
        }
        else if(it == "top")
        {
            if(stack.size()==0)
            {
                //cout<< -1<<"\n";
                answer.push_back(-1);
            }
            else
            {
                //cout<< stack[stack.size()-1]<<"\n";
                answer.push_back(stack[stack.size()-1]);
            }
        }
    }

    for(i = 0; answer.size();i++)
    {
        cout << answer[i] << "\n";
    }
    return 0;
}