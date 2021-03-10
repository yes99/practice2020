#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int n, p;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> n >> p;
	int flag = 0;
	int Pcnt =0;
	for (int i = 1; i < p; i++)
	{
		if (p % i == 0)
		{
			Pcnt++;
		}
	}
	if (Pcnt == 1)
	{
		flag++;
	} // p가 소수인지 판별
	int small;
	if (n < p)
	{
		small = n;
	}
	else
	{
		small = p;
	}
	int Gcnt=0;
	for (int i = 1; i < small; i++)
	{
		if (n % i == 0 && p % i == 0)
		{
			Gcnt++;
		}
	}
	if (Gcnt == 1)
	{
		flag++;
	}

	if (flag == 2)
	{
		oo << "True";
	}
	else
	{
		oo << "False";
	}
	ii.close();
	oo.close();
	return 0;
}