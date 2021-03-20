#include <iostream>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;
// ii >>
// oo <<

bool c1(int a, int b)
{
	return a > b;
}

bool c2(int a, int b)
{
	return a < b;
}


int main()
{
	ifstream ii("D:\\input.txt");
	//ifstream ii("input.txt");

	ofstream oo("D:\\output.txt");
	//ofstream oo("output.txt");
	string a = "1523";
	string b = "200";
	int arr1[4];
	char u[4];
	char d[4];
	int i, j, k;
	for (i = 0; i < 4; i++)
	{
		arr1[i] = a[i] ;
	}
	sort(arr1, arr1+4, c1);
	for (i = 0; i < 4; i++)
	{
		u[i] = arr1[i];
		cout << u[i];
	}
	cout << endl;
	sort(arr1, arr1 + 4, c2);
	for (i = 0; i < 4; i++)
	{
		d[i] = arr1[i];
		cout << d[i];
	}
	cout << endl;
	atoi(u);
	atoi(d);
	for (i = 0; i < 4; i++)
	{
		cout << u[i];
	}
	/*while (1)
	{
		sort(arr1, arr2);
	}*/

	
	ii.close();
	oo.close();
	return 0;
}