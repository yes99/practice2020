#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int num;
	int num1;
	int co;
	int degree;
	int a[101] = { 0 , };
	int i, j, k;

	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> num;
	for (i = 0; i < num; i++)
	{
		ii >> co >> degree;
		a[co] = degree;
	}
	ii >> num1;
	for (i = 0; i < num1; i++)
	{
		ii >> co >> degree;
		a[co] = a[co] + degree;
	}
	int key;
	if (num > num1)
	{
		key = num;
	}
	else
	{
		key = num1;
	}

	for (i = 100; i >= 0; i--)
	{
		if (a[i] != 0)
		{
			oo << i << " " << a[i] << " ";
		}
	}

	ii.close();
	oo.close();
	return 0;
}