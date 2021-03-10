#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<

int main()
{
	string base;
	int ex;
	char cal[50];
	char cal2[50];
	char sum[50];
	int i, j, k;
	int n = 50;
	int t = 0;


	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");

	ii >> base >> ex;
	for (i = 0; i < n; i++)
	{
		cal[i] = '0';
		cal2[i] = 0;
		sum[i] = 0;
	}
	int lbase = base.length();
	for (i = 0; i < lbase; i++)
	{
		cal[n - lbase + i] = base[i];
	}

	int mul, ten=1; // 문자를 숫자화 시키기
	int finalmul = 0;
	for (i = n-1; i >= 1; i--)
	{
		mul = cal[i] - '0';
		for (j = 0; j < n-i-1; j++)
		{
			if (i == n-1)
			{
				break;
			}
			ten = ten * 10;
		}
		finalmul = finalmul + mul * ten;
	}


	for (i = 0; i < n; i++)
	{
		cal[i] = 0;
	}
	for (i = 0; i < lbase; i++)
	{
		cal[n - lbase + i] = base[i] - '0' ;
	}


	for (i = 0; i < ex-1; i++) //몇번 곱할지
	{
		for (j = n-1; j >= 0; j--)
		{
			t = finalmul * cal[j] + sum[j];
			sum[j - 1] = sum[j - 1] + t / 10;
			sum[j] = t % 10;
		}
		for (k = 0; k < 50; k++)
		{
			cal[k] = sum[k];
			sum[k] = 0;
		}
	}

	//출력
	int key = 0;
	for (j = 0; j < 50; j++)
	{
		if (cal[j] != 0)
		{
			key = j;
			break;
		}
	}
	for (j = key; j < 50; j++)
	{
		oo << int(cal[j]);
	}

	ii.close();
	oo.close();
	return 0;
}