#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

// ii >>

// oo <<
int a[100][100];

int check(int a[100][100], int i, int j)
{
	int cnt = 0;
	//if(a[i+2][j+3] == 1 && a[i][j] == 2)
	if (a[i + 2][j + 3] == 1)
	{
		cnt++;
	}
	if (a[i + 3][j + 2] == 1)
	{
		cnt++;
	}
	if (a[i + 3][j - 2] == 1)
	{
		cnt++;
	}
	if (a[i + 2][j - 3] == 1)
	{
		cnt++;
	}
	if (a[i - 2][j + 3] == 1)
	{
		cnt++;
	}
	if (a[i - 2][j - 3] == 1)
	{
		cnt++;
	}
	if (a[i - 3][j - 2] == 1)
	{
		cnt++;
	}
	if (a[i - 3][j + 2] == 1)
	{
		cnt++;
	}

	return cnt;
}



int main()
{
	//ifstream ii("D:\\input.txt");
	ifstream ii("input.txt");
	//ofstream oo("D:\\output.txt");
	ofstream oo("output.txt");

	int size;
	int p;
	int i, j;
	memset(a, -1, sizeof(a));
	ii >> size;

	for (i = 1; i <= size; i++)
	{
		for (j = 1; j <= size; j++)
		{
			ii >> p;
			a[i][j] = p;
		}
	}
	//Debug
	for (i = 0; i <= size + 1; i++)
	{
		for (j = 0; j <= size + 1; j++)
		{
			cout << a[i][j];
		}
		cout << endl;
	}
	int t = 0;
	int bluf;
	int ele = 0; // 잡은 폰의 갯수
	int nn = 0; //99가 나와서 멈추는 경우
	int cnt = 0;
	int oricnt = 1;
	int plus = 0;
	int c;
	int answer = 0;
	int flag = 0;
	int plusall = 0;
	while (t < 2)
	{
		cout << endl << t << endl;
		for (i = 1; i <= size; i++)
		{
			for (j = 1; j <= size; j++)
			{
				if (a[i][j] == 2)
				{

					plus++;
					answer = answer + check(a, i, j);
					cout << i << " " << j <<" temp answer " << answer<<endl;
					if (a[i + 2][j + 3] != -1)
					{
						a[i + 2][j + 3] = 3;
						cnt++;
					}
					if (a[i + 2][j - 3] != -1)
					{
						a[i + 2][j - 3] = 3;
						cnt++;
					}
					if (a[i + 3][j + 2] != -1)
					{
						a[i + 3][j + 2] = 3;
						cnt++;
					}
					if (a[i + 3][j - 2] != -1)
					{
						a[i + 3][j - 2] = 3;
						cnt++;
					}
					if (a[i - 2][j + 3] != -1)
					{
						a[i - 2][j + 3] = 3;
						cnt++;
					}
					if (a[i - 2][j - 3] != -1)
					{
						a[i - 2][j - 3] = 3;
						cnt++;
					}
					if (a[i - 3][j - 2] != -1)
					{
						a[i - 3][j - 2] = 3;
						cnt++;
					}
					if (a[i - 3][j + 2] != -1)
					{
						a[i - 3][j + 2] = 3;
						cnt++;
					}
					cout << "oricnt " << oricnt << " plus " << plus << endl;

					/*if (oricnt == plus)
					{
						oricnt = oricnt + cnt;
						plus = 0;
						flag = 1;
					}*/


				}
			}
			/*if (flag == 1)
			{
				flag = 0;
			}*/
		}
		t++;
		//Debug
		for (i = 0; i <= size + 1; i++)
		{
			for (j = 0; j <= size + 1; j++)
			{
				cout << a[i][j];
			}
			cout << endl;
		}
		cout << endl << endl;
		for (i = 1; i <= size ; i++)
		{
			for (j = 1; j <= size; j++)
			{
				if (a[i][j] == 3)
				{
					a[i][j] = 2;
				}
			}
		}
		for (i = 0; i <= size + 1; i++)
		{
			for (j = 0; j <= size + 1; j++)
			{
				cout << a[i][j];
			}
			cout << endl;
		}
		cout << endl << endl;

		/*for(i = 1 ; i <= size; i++)
		{
			for(j =1 ; j<=size; j++)
			{
				if(a[i][j] == 2)
				{
					a[i][j] = 1;
				}
			}
			cout<<endl;
		}*/
		//cout << "t " << t << endl;
		//cout << "nn "<< nn << endl;
		//cout << "ele" << ele << endl;

		if (cnt == ele)
		{
			break;
		}
		nn = 0;
	}
	cout << "아마 답 " << answer << endl;


	for (i = 0; i <= size + 1; i++)
	{
		for (j = 0; j <= size + 1; j++)
		{

			cout << a[i][j];
		}
		cout << endl;
	}
	cout << endl;
	
	cout << "아마 답 " << answer << endl;
	oo << answer;
	ii.close();
	oo.close();
	return 0;

}








/*c = check(a, i, j);
					if(c == 1)
					{
						if (a[i + 2][j + 3] == 1)
						{
							ele++;
						}
						a[i + 2][j + 3] =2;
						cnt++;
					}
					if (c == 2)
					{
						if (a[i + 3][j + 2] == 1)
						{
							ele++;
						}
						a[i + 3][j + 2] = 2;
						cnt++;
					}
					if (c == 3)
					{
						if (a[i + 3][j - 2] == 1)
						{
							ele++;
						}
						a[i + 3][j - 2] = 2;
						cnt++;
					}
					if (c == 4)
					{
						if (a[i + 2][j - 3] == 1)
						{
							ele++;
						}
						a[i + 2][j - 3] = 2;
						cnt++;
					}
					if (c == 5)
					{
						if (a[i - 2][j + 3] == 1)
						{
							ele++;
						}
						a[i - 2][j + 3] = 2;
						cnt++;
					}
					if (c == 6)
					{
						if (a[i - 2][j - 3] == 1)
						{
							ele++;
						}
						a[i - 2][j - 3] = 2;
						cnt++;
					}
					if (c == 7)
					{
						if (a[i - 3][j - 2] == 1)
						{
							ele++;
						}
						a[i - 3][j - 2] = 2;
						cnt++;
					}
					if (c == 8)
					{
						if (a[i - 3][j + 2] == 1)
						{
							ele++;
						}
						a[i - 3][j + 2] = 2;
						cnt++;
					}
					if(c == 99)
					{
						nn++;
					}*/




