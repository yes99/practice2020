#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	string big;
	string div;
	int i, j;
	int origin;
	int cnt = 0;
	int answer[10];
	int surplus[5];
	char cmpsurplus[5];
	char cmpdiv[5];

	ifstream ii("C:\\이현석\\input.txt");
	//ifstream ii("input.txt");

	ofstream oo("C:\\이현석\\output.txt");
	//ofstream oo("output.txt");
	getline(ii, big);
	getline(ii, div);
	int abig[10]; //97543421
	int adiv[5]; //11
	int ldiv = div.length()-1; //8
	int lbig = big.length()-1; //2

	for (i = 0; i < lbig+1; i++)
	{
		abig[i] = big[i]-'0';
	}
	for (i = 0; i < ldiv+1; i++)
	{
		adiv[i] = div[i] - '0';
		cmpdiv[i] = div[i];
	}
	//확인
	oo << "나누기 : ";
	for (i = 0; i < ldiv + 1; i++)
	{
		oo << cmpdiv[i];
	}oo << endl;
	/*
	for (i = 0; i < 10; i++)
	{
		oo << int(abig[i]);
	}oo << endl;
	for (i = 0; i < 5; i++)
	{
		oo << int(adiv[i]);
	}oo << endl;
	*/
	int key;
	int position= ldiv;
	for (i = ldiv; i < lbig; i++)
	{
		origin = i;
		do
		{
			do
			{
				for (j = ldiv; j >= 0; j--)
				{//abig[i] = abig[i] - adiv[i];
					if (abig[i] - adiv[j] < 0)
					{
						abig[i - 1] = abig[i - 1] - 1;
						abig[i] = abig[i] + 10;
					}
					abig[i] = abig[i] - adiv[j];
					i--;
				}
			} while (j > -1);
			cnt++;
			//여기가 고장
			for (j = 0; j < ldiv+1; j++)
			{
				surplus[j] = abig[position];
				cmpsurplus[j] = abig[position] + '0';
				position++;
			}
			position = i;
			//확인
			oo << "나머지 : ";
			for (j = 0; j < ldiv + 1; j++)
			{
				oo << cmpsurplus[j];
			}oo << endl;
			i = origin;
			key = strcmp(cmpdiv, cmpsurplus);
		} while (key == -1);

	}
	answer[i] = cnt;



	ii.close();
	oo.close();
	return 0;
}