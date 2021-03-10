#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int num;
    int width;
    int i, j, k;
    int score;
    cin >> num;
    int arr[2][100001];
    int sum[2][100001];
    int answer[100001];
    int push=0;
    for (i = 0; i < num; i++)
    {
        cin >> width;
        for (k = 0; k < 2; k++)
        {
            for (j = 1; j <= width; j++)
            {
                cin >> score;
                arr[k][j] = score;
            }
        }
        sum[0][1] = arr[0][1];
        sum[1][1] = arr[1][1];

        for (j = 2; j <= width+1; j++)
        {
            sum[0][j] = max(sum[1][j-1], sum[1][j-2])+ arr[0][j];
            sum[1][j] = max(sum[0][j-1], sum[0][j-2])+ arr[1][j];
        }
        int input = max(sum[0][width], sum[1][width]);
        answer[push] = input;
        push++;
    }

    for(i =0; i <push;i++)
    {
        cout<<answer[i]<<endl;
    }
}
