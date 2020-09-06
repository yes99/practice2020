#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	string hamming;

	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	getline(ii, hamming);
	int c1=0, c2=0, c3=0;
	int i, j, k;
	int check[3];
	int h;
	for (i = 0; i < 7; i=i+2)
	{
		if ( hamming[i] == 49)
		{
			c1++;
		}
	}
	if (c1 % 2 == 1)
	{
		check[2] = 1;
	}
	else
	{
		check[2] = 0;
	}
	for (j = 1; j < 7; j++)
	{
		if (hamming[j] == 49)
		{
			c2++;
		}
		if (j == 2)
		{
			j = j + 2;
		}
	}
	if (c2 % 2 == 1)
	{
		check[1] = 1;
	}
	else
	{
		check[1] = 0;
	}

	for (k = 3; k < 7; k++)
	{
		if (hamming[k] == 49)
		{
			c3++;
		}
	}
	if (c3 % 2 == 1)
	{
		check[0] = 1;
	}
	else
	{
		check[0] = 0;
	}
	//그래서 나온 2진수
	//oo << check[0]<<check[1]<<check[2] << endl;
	
	int error = 4 * check[0] + 2 * check[1] + check[2] -1;
	if (hamming[error] == 49)
	{
		hamming[error] = 48;
	}
	else
	{
		hamming[error] = 49;
	}
	int f;
	for (f = 0; f < 7; f++)
	{
		oo << hamming[f];
	}


	ii.close();
	oo.close();
	return 0;
}