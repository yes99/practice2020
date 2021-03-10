#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int roomnum;
	int first[100] = { 0, };
	int second[100] = { 0, };
	int sum[100] = { 0, };
	int n = 100 - 1;;
	int i, j;
	int t;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> roomnum;
	if (roomnum == 0)
	{
		oo << 1;
		ii.close();
		return 0;
	}
	else if (roomnum == 1)
	{
		oo << 2;
		ii.close();
		return 0;
	}
	else if (roomnum == 2)
	{
		oo << 3;
		ii.close();
		return 0;
	}

	first[n] = 1;
	second[n] = 1;

	for (i = 2; i < roomnum+1; i++)
	{
		for (j = n; j >0; j--)
		{
			t = first[j] + second[j] + sum[j];
			sum[j - 1] = t / 10;
			sum[j] = t % 10;
		}
		for (j = 0; j < n + 1; j++)
		{
			first[j] = second[j];
		}
		for (j = 0; j < n + 1; j++)
		{
			second[j] = sum[j];
		}
		for (j = 0; j < n + 1; j++)
		{
			sum[j]=0;
		}
	}
	int key = 0;
	for (j = 0; j < n+1; j++)
	{
		if (second[j] != 0)
		{
			key = j;
			break;
		}
	}

	for (j = key; j < n+1; j++)
	{
		oo << second[j];
	}


	ii.close();
	oo.close();
	return 0;
}