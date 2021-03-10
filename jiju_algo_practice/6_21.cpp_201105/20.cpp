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
	string country;
	int g, s, b; // gold silver bronze
	string acountry[200];
	int amedal[200][3];
	int n = 200;
	int i, j, k;
	int t;
	string st;
	int flag[200] = { 0, };
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> num;

	for (i = 0; i < num; i++)
	{
		ii >> country;
		ii >> g >> s >> b;
		acountry[i] = country;
		amedal[i][0] = g;
		amedal[i][1] = s;
		amedal[i][2] = b;
	}



	/*for (i = 0; i < 5; i++)
	{
		oo << acountry[i] << " " << amedal[i][0] << " " << amedal[i][1] << " " << amedal[i][2] << endl;
	}
	oo << endl << endl << endl;
	*/

	for (i = 1; i < n; i++)
	{
		for (j = i - 1; j >= 0; j--)
		{
			if (amedal[j][0] < amedal[j + 1][0]) //금메달
			{
				t = amedal[j][0];
				amedal[j][0] = amedal[j + 1][0];
				amedal[j + 1][0] = t;

				t = amedal[j][1];
				amedal[j][1] = amedal[j + 1][1];
				amedal[j + 1][1] = t;

				t = amedal[j][2];
				amedal[j][2] = amedal[j + 1][2];
				amedal[j + 1][2] = t;

				st = acountry[j];
				acountry[j] = acountry[j + 1];
				acountry[j + 1] = st;
			}
			else if (amedal[j][0] == amedal[j + 1][0]) //금메달 같다면
			{
				if (amedal[j][1] < amedal[j + 1][1]) // 은메달 비교
				{
					t = amedal[j][0];
					amedal[j][0] = amedal[j + 1][0];
					amedal[j + 1][0] = t;

					t = amedal[j][1];
					amedal[j][1] = amedal[j + 1][1];
					amedal[j + 1][1] = t;

					t = amedal[j][2];
					amedal[j][2] = amedal[j + 1][2];
					amedal[j + 1][2] = t;

					st = acountry[j];
					acountry[j] = acountry[j + 1];
					acountry[j + 1] = st;
				}
				else if (amedal[j][1] == amedal[j + 1][1]) //은메달 같다면
				{
					if (amedal[j][2] < amedal[j + 1][2]) //동메달 비교
					{
						t = amedal[j][0];
						amedal[j][0] = amedal[j + 1][0];
						amedal[j + 1][0] = t;

						t = amedal[j][1];
						amedal[j][1] = amedal[j + 1][1];
						amedal[j + 1][1] = t;

						t = amedal[j][2];
						amedal[j][2] = amedal[j + 1][2];
						amedal[j + 1][2] = t;

						st = acountry[j];
						acountry[j] = acountry[j + 1];
						acountry[j + 1] = st;
					}
					else if (amedal[j][2] == amedal[j + 1][2]) // 동메달도 같으면
					{

						if (acountry[j] > acountry[j + 1])
						{
							st = acountry[j];
							acountry[j] = acountry[j + 1];
							acountry[j + 1] = st;
						}
					}
				}
			}
		}
	}



	
	for (i = 0; i < num; i++)
	{
		if (amedal[i][0] == amedal[i + 1][0] && amedal[i][1] == amedal[i + 1][1] && amedal[i][2] == amedal[i + 1][2])
		{
				flag[i + 1] = flag[i] + 1;
		}
	}







	for (i = 0; i < num; i++)
	{
		if (flag[i] == 0)
		{
			if (i == 0)
			{
				oo << "1st" << " ";
				oo << acountry[i] << " " << amedal[i][0] << " " << amedal[i][1] << " " << amedal[i][2] << endl;

			}
			else if (i == 1)
			{
				oo << "2nd" << " ";
				oo << acountry[i] << " " << amedal[i][0] << " " << amedal[i][1] << " " << amedal[i][2] << endl;
			}
			else if (i == 2)
			{
				oo << "3rd" << " ";
				oo << acountry[i] << " " << amedal[i][0] << " " << amedal[i][1] << " " << amedal[i][2] << endl;
			}
			else
			{
				oo << i + 1 << "th ";
				oo << acountry[i] << " " << amedal[i][0] << " " << amedal[i][1] << " " << amedal[i][2] << endl;
			}
		}
		else
		{
			if (i - flag[i] + 1 == 1) 
			{
				oo << "1st" << " ";
				oo << acountry[i] << " " << amedal[i][0] << " " << amedal[i][1] << " " << amedal[i][2] << endl;
			}
			else if (i - flag[i] + 1 == 2)
			{
				oo << "2nd" << " ";
				oo << acountry[i] << " " << amedal[i][0] << " " << amedal[i][1] << " " << amedal[i][2] << endl;
			}
			else if (i - flag[i] + 1 == 3)
			{
				oo << "3rd" << " ";
				oo << acountry[i] << " " << amedal[i][0] << " " << amedal[i][1] << " " << amedal[i][2] << endl;
			}
			else
			{
				oo << i - flag[i] + 1 << "th ";
				oo << acountry[i] << " " << amedal[i][0] << " " << amedal[i][1] << " " << amedal[i][2] << endl;
			}



		}
	}


	ii.close();
	oo.close();
	return 0;
}