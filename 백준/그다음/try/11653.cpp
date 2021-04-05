#include <iostream>
#include <vector>
using namespace std;

const long long MAX = 10000000;

int minFactor[MAX];
vector<long long> prime; //소수
//에라토스테네스의 체
void eratosthenes(void)
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
    for (int i = 2;i < MAX; i++)
    {
        if (minFactor[i] == i)
        {
            prime.push_back(i);
        }
    }
}


int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    eratosthenes();
    long long number;

    cin>>number;
    int i , j ,k;

    /*for(i=0; i <10; i++)
    {
        cout << prime[i] << " ";
    }*/
    while(number>1)
    {
        for(i = 0 ; i < number; i++)
        {
            if(number % prime[i] == 0)
            {
                cout << prime[i]<<"\n";
                number = number / prime[i];
                break;
            }
        }
    }
}
