#include <iostream>
using namespace std;
void bubble(int a[], int n)
{
	int flag, t, i, j;
	//int a[16] = { 1,1,2,3,4,5,5,5,5,6,6,6,7,7,8,8 };

	for (i = 1; i <= n - 1; i++)
	{
		flag = 0;
		for (j = 0; j < n - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
				flag = 1;
			}
		}
		if (flag == 0)
		{
			break;
		}
	}
}
int main()
{
	int flag, n, t, i, j;
	int a[16] = { 1,1,2,3,4,5,5,5,5,6,6,6,7,7,8,8 };
	n = 16;

	/*for (i = 1; i <= n - 1; i++)
	{
		flag = 0;
		for (j = 0; j < n - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
				flag = 1;
			}
		}
		if (flag == 0)
		{
			break;
		}
	}
	*/
	bubble(a, n);
	for (i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;


}

