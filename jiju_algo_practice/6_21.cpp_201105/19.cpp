#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int child;
	int num;
	double height;
	double weight;
	int i, j, k, flag;
	double a[100][3];
	double t1, t2, t3;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> child;

	for(i = 0 ; i < child ; i++)
	{
		ii >> num >> height >> weight;
		a[i][0] = num;
		a[i][1] = height;
		a[i][2] = weight;
	}

	for (i = 1; i < child - 1; i++)
	{
		flag = 0;
		for (j = 0; j < child - i; j++)
		{
			if (a[j][1] == a[j + 1][1])
			{
				if (a[j][2] > a[j + 1][2])
				{
					t2 = a[j][1];
					a[j][1] = a[j + 1][1];
					a[j + 1][1] = t2;
			

					t1 = a[j][0];
					a[j][0] = a[j + 1][0];
					a[j + 1][0] = t1;

					t3 = a[j][2];
					a[j][2] = a[j + 1][2];
					a[j + 1][2] = t3;
					flag = 1;
				}
			}
			else if (a[j][1] > a[j + 1][1])
			{
				t2 = a[j][1];
				a[j][1] = a[j + 1][1];
				a[j + 1][1] = t2;


				t1 = a[j][0];
				a[j][0] = a[j + 1][0];
				a[j + 1][0] = t1;

				t3 = a[j][2];
				a[j][2] = a[j + 1][2];
				a[j + 1][2] = t3;
				flag = 1;
			}
		}
		if (flag == 0)
		{
			break;
		}
	}


	for (i = 0; i <child; i++)
	{
		oo << a[i][0]  << endl;
	}
	//<<" "  << a[i][1] <<" " << a[i][2]
	ii.close();
	oo.close();
	return 0;
}