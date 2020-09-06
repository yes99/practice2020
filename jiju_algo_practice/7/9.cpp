#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	int a, b;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> a >> b;
	int j;
	int cnt;
	int prime = 0;
	for (int i = 1; i < b + 1; i++)
	{
		cnt = 0;
		j = 1;
		while (j < i+1)
		{
			if (a%j == 0 && i%j ==0)
			{
				cnt++;
			}
			j++;
		}
		if (cnt == 1)
		{
			prime++;
		}
	}

	oo << prime;
	ii.close();
	oo.close();
	return 0;
}