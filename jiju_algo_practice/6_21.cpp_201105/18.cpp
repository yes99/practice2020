#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int team;
	int athe;
	double height;
	///////
	double Harray[50]; // heightarray;
	double Aarray[50]; // answer array;
	int Narray[50]; // 같이 돌려서 순위 뽑아야함
	int Parray[50];
	int i, j, k;
	double t;
	int tnum;
	int a, b, c; // 버블소트 전용
	double sum=0;
	double ave;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> team;

	for (i = 0; i < team; i++)
	{
		ii >> athe;
		for (j = 0; j < athe; j++)
		{
			ii >> height;
			Harray[j] = height;
		}

		for (a = 1; a <= athe - 1; a++)
		{
			for (b = 0; b < athe - a; b++)
			{
				if (Harray[b] > Harray[b + 1])
				{
					t = Harray[b];
					Harray[b] = Harray[b + 1];
					Harray[b + 1] = t;
				}
			}
		}
		//디버깅
		//for (j = 0; j < athe; j++)
		//{
		//	oo << Harray[j] << " ";
		//}
		//oo << endl;
		////
		for (j = 1; j < athe-1; j++)
		{
			sum = sum + Harray[j];
		}
		ave = sum / (athe-2);
		Aarray[i] = ave;

		//초기화 시켜주기
		sum = 0;
		for (j = 0; j < athe; j++)
		{
			Harray[j] = 0;
		}
	}
	for (i = 0; i < team; i++)
	{
		Narray[i] = i + 1;
		Parray[i] = i + 1;
	}
	/*for (i = 0; i < team; i++)
	{
		oo << Aarray[i] << " ";
	}*/

	/*for (i = 0; i < team; i++)
	{
		oo << Aarray[i] << " ";
	}
	oo << endl;*/

	for (i = 1; i < team - 1; i++)
	{
		for (j = 0; j < team - i; j++)
		{
			if (Aarray[j] < Aarray[j + 1])
			{
				t = Aarray[j];
				Aarray[j] = Aarray[j + 1];
				Aarray[j + 1] = t;
				tnum = Narray[j];
				Narray[j] = Narray[j + 1];
				Narray[j + 1] = tnum;
			}
		}
	}
	//for (i = 0; i < team; i++)
	//{
	//	oo << Aarray[i] << " ";
	//}
	oo << endl;
	for (i = 1; i <= team - 1; i++)
	{
		for (j = 0; j < team - i; j++)
		{
			if (Narray[j] > Narray[j + 1])
			{
				tnum = Narray[j];
				Narray[j] = Narray[j + 1];
				Narray[j + 1] = tnum;
				t = Parray[j];
				Parray[j] = Parray[j + 1];
				Parray[j + 1] = t;
			}
		}
	}


	for (i = 0; i < team; i++)
	{
		oo << Parray[i] << endl;
	}
	ii.close();
	oo.close();
	return 0;
}