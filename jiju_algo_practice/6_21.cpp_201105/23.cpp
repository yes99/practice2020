#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int number;
	double find;
	double num;
	double Anum[100000];
	int n = 100;
	int i, j, k;
	double temp;
	int t;
	int t1, t2;
	int flag = 0;

	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> number;
	ii >> find;
	int high = number;
	int low = 1;
	for (i = 0; i < number; i++)
	{
		ii >> num;
		Anum[i] = num;
	}
	for (i = 1; i < number; i++)
	{
		for (j = i - 1; j >= 0; j--)
		{
			if (Anum[j] > Anum[j + 1])
			{
				temp = Anum[j];
				Anum[j] = Anum[j + 1];
				Anum[j + 1] = temp;
			}
			else
			{
				break;
			}
		}
	}
	for (i = number; i > 0; i--)
	{
		Anum[i + 1] = Anum[i];
	}

	/*for (i = 1; i < number+1; i++)
	{
		cout << Anum[i] << endl;
	}*/
	//일단 모두 입력 완료

	while (low <= high)
	{
		t = (high - low) / 3;
		t1 = low + t;
		t2 = t1 + t;
		oo << low << " " << high << endl;

		if (find == Anum[t1] || find == Anum[t2])
		{
			break;
		}
		if (find < Anum[t1])
		{
			high = t1 -1;
		}
		else if (find > Anum[t1] && find < Anum[t2])
		{
			high = t2 -1;
			low = t1 +1;
		}
		else if (find >Anum[t2 ])
		{
			low = t2 +1;
		}

	}
	
	ii.close();
	oo.close();
	return 0;
}