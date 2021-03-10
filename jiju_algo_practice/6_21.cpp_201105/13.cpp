#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int row, colum;
	int arr[20][50] = { 0, };
	int m = 20;
	int n = 50;
	int i, j, k;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> row >> colum;
	arr[0][0] = 1;
	for (i = 1; i < m; i++)
	{
		arr[i][0] = 1;
		arr[i][2 * i] = 1;
		arr[i][1] = i;
		arr[i][2 * i - 1] = i;
	}
	for (i = 2; i < m; i++)
	{
		for (j = 2; j < 2 * i - 1; j++)
		{
			arr[i][j] = arr[i - 1][j - 2] + arr[i - 1][j-1] + arr[i - 1][j];
		}
	}


	/*for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			oo << arr[i][j] << " ";
		}
		oo << endl;
	}
	*/
	oo << arr[row][colum];
	
	ii.close();
	oo.close();
	return 0;
}