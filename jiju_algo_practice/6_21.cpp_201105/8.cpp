#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int prime[100];
	int i, j, flag;
	int n = 999, k = 1;
	prime[1] = 2;

	int num;

	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> num;
	for (i = 3; i <= n; i++)
	{
		flag = 0;
		for (j = 1; j <= k; j++)
		{
			if (i % prime[j] == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			k++;
			prime[k] = i;
		}
		if (k == 99)
		{
			break;
		}
	}

	/*for (i = 1; i <= k; i++)
	{
		oo << prime[i] << "\t";
	}*/

	for (i = 1; i < k; i++)
	{
		if (prime[i] > num)
		{
			break;
		}
		if (prime[i] == num)
		{
			oo << "x";
		}
		else
		{
			oo << num%prime[i];
		}
	}

	ii.close();
	oo.close();
	return 0;
}