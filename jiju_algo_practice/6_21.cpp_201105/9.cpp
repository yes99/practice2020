#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int nation;
	string input;
	char cal[50];
	char plus[50];
	char sum[50];
	int i, j, k;
	int n = 50;
	int t = 0;
	
	
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	
	ii >> nation; ii.ignore();

	//sum 초기화


	for (i = 0; i < nation; i++)
	{
		//cal 초기화
		for (j = 0; j < 50; j++)
		{
			cal[j] = 0;
			sum[j] = 0;
			plus[j] = 0;
		}

		ii >> input;
		int l = input.length();
		for (j = 0; j < l; j++)
		{
			cal[50 - l + j] = input[j] - '0';
		}
		for (j = 0; j < 22096; j++) // 이만큼 더하기를 해야함
		{
			for (k = n - 1; k >= 1; k--)
			{
				t = plus[k] + cal[k]+ sum[k];
				sum[k - 1] = t / 10;
				sum[k] = t % 10;
			}
			for (k = 0; k < 50; k++)
			{
				plus[k] = sum[k];
				sum[k] = 0;
			}
			
		}
		/*for (j = 0; j < 50; j++) //시범삼아 출력
		{
			oo<<int(sum[j]);
		}*/
		int key = 0;
		for (j = 0; j < 50; j++)
		{
			if (plus[j] != 0)
			{
				key = j;
				break;
			}
		}
		for (j = key; j < 50; j++)
		{
			oo << int(plus[j]);
		}

		oo << endl;
	}


	ii.close();
	oo.close();
	return 0;
}