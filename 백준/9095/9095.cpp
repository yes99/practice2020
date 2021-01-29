#include <iostream>
using namespace std;

int main()
{
    int i, j;
    int answer[1001];
    int input;
    answer[0] = 0;
    answer[1] = 1;
    answer[2] = 2;
    answer[3] = 4;
    for (i = 4; i <= 11; i++)
    {
        input = answer[i - 1] + answer[i - 2] + answer[i - 3];
        answer[i] = input;
    }
    int num;
    cin>>num;
    int n;
    int output[12];
    for(i = 0 ; i < num; i++)
    {
        cin >> n;
        output[i] = answer[n];
    }
    for(i = 0 ; i < num; i++)
    {
        cout << output[i] <<endl;
    }
    

}