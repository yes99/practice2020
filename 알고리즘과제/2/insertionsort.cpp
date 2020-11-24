#include <iostream>
using namespace std;

int main()
{
	int a[12] = { 10,1,1,8,5,8,2,5,3,0,7,4 };
	int n, i, j, t;
	n = 12;

	for (i = 1; i < n; i++)
	{
		for (j = i - 1; j >= 0; j--)
		{
			if (a[j] > a[j + 1])
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
			else
			{
				break;
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