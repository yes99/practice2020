#include <iostream>
using namespace std;


int main()
{
	int a[5] = { 3,9,1,5,7 };
	int n, i, j, s, t;
	n = 5;
	for (i = 0; i < n - 1; i++)
	{
		s = i;
		for (j = i + 1; j < n; j++)
		{
			if (a[s] > a[j])
			{
				s = j;
			}
		}
		t = a[i];
		a[i] = a[s];
		a[s] = t;
	}


	for (i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}

	cout << endl;
	return 0;
}