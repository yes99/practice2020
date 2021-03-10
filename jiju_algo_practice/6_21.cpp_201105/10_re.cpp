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
	//입력 받는 애들
	char accum[50];
	char cal[50];
	char result[100];
	int i, j, k;
	int n = 50;
	int t = 0;
	int lbase;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> base >> ex;
	lbase = base.length();
	for (i = 0; i < 100; i++)
	{
		result[i] = 0;
	}
	for (i = 0; i < 50; i++)
	{
		accum[i] = 0;
		cal[i] = 0;
	}
	for (i = 0; i < lbase; i++)
	{
		accum[n - lbase + i] = base[i] - '0';
		cal[n - lbase + i] = base[i] - '0';
	}
	 
	/*//Debug 체크
	for (i = 0; i < 50; i++)
	{
		oo << int(accum[i]);
	}
	oo << endl;
	for (i = 0; i < 50; i++)
	{
		oo << int(cal[i]);
	}
	oo << endl;
	*/

	for (k = 0; k < ex-1; k++) // 12번 돌릴꼬야
	{
		for (i = n-1; i > 1; i--)
		{
			for (j = n-1; j > 1; j--)
			{
				t = int(accum[i]) * int(cal[j]) +int( result[i + j]);
				(result[i + j - 1]) = (result[i + j - 1]) + (t / 10);
				result[i + j] = t % 10;
			}
		}

		for (i = 49; i >0; i--)
		{
			accum[i] = result[i +49];
			result[i+50] = 0;
		}
		
		
	
	}


	//출력
	int key = 0;
	for (j = 0; j < 50; j++)
	{
		if (accum[j] != 0)
		{
			key = j;
			break;
		}
	}
	for (j = key; j < 50; j++)
	{
		oo << int(accum[j]);
	}


	ii.close();
	oo.close();
	return 0;
}