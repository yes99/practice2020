#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1000000;

int minFactor[MAX];
vector<int> prime; //소수
//에라토스테네스의 체
int main(void)
{
    minFactor[0] = minFactor[1] = -1;
    for (int i = 2; i < MAX; i++)
    {
        minFactor[i] = i;
    }

    for (int i = 2; i * i < MAX; i++)
    {
        if (minFactor[i] == i)
        {
            for (int j = i * i; j < MAX; j += i)
            {
                if (minFactor[j] == j)
                {
                    minFactor[j] = i;
                }
            }

        }

    }
    //홀수인 소수를 저장
    for (int i = 3; i < MAX; i++)
    {
        if (minFactor[i] == i)
        {
            prime.push_back(i);
        }
    }
}