#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

const int MAX = 300000 + 1;
int P;
int visited[MAX];
void DFS(int num)
{
    visited[num]++;
    //반복구간이 한번 반복되었다는 것을 의미
    if (visited[num] == 3)
        return;
    int sum = 0;
    while (num)
    {
        sum += (int)pow((num % 10), P);
        num /= 10;
    }
    DFS(sum);
}

int main(void)
{
    int A;
    cin >> A >> P;
    DFS(A);
    int result = 0;
    //한번만 등장한 숫자들이 반복구간에 속하지 않은 숫자들
    for (int i = 0; i < MAX; i++)
        if (visited[i] == 1)
            result++;
    cout << result << "\n";
    return 0;
}
