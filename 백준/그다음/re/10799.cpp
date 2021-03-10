#include <iostream>
#include <string>
#include <stack>
using namespace std;
string str;
int pipe(const string &str)
{
    stack<char> st;
    int result = 0;
    for (int i = 0; i < str.length(); i++)
    {
        //여는 괄호면 스택에 넣는다.
        if (str[i] == '(')    // 막대기가 하나씩 시작된다
        {
            st.push(str[i]);
        }
        //닫는 괄호면 이 괄호가 레이저인지, 파이프 끝인지 알아본다.
        else // )가 튀어 나올때
        {
            st.pop();
            //레이저면
            if (str[i - 1] == '(') // ( 가 나오면  밑에 안잘리고 남아있는 파이프들을 다 더해야함
            {
                result += st.size(); //잘린 갯수 추가.
            }
            //파이프의 끝이면
            else // 파이프가 끝나서 잘려 버리면, 잘린거 하나만 카운트 하고 나머지는 
            {
                result++; //닫혀서 잘려진 갯수 추가.
            }
        }
    }
    return result;
}
int main()
{
    cin >> str;
    cout << pipe(str);
}