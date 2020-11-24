#include <iostream>
using namespace std;

int main()
{
	int n, t, i, j;
	int a[9] = { 8,2,8,2,5,2,4,10,5 };
	n = 9;

	for (i = 1; i <= n - 1; i++)
	{
		for (j = 0; j < n - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
		}
	}




	for (i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;


}