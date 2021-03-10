#include <iostream>
using namespace std;

int main()
{
	int a[] = { 72 , 60 , 21 , 38 , 51 , 80 , 95 , 70 , 95, 60 };
	int b[100];
	int n = 10;
	int i, j;

	for (i = 0; i < n; i++)
	{
		b[i] = 1;
	}
	
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (a[i] < a[j])
			{
				b[i]++;
			}
			else if (a[i] > a[j])
			{
				b[j]++;
			}
		}
	}
	
	cout << "DATA RANKING" << endl;
	for ( int i = 0; i < n; i++)
	{
		cout << a[i] << "\t" << b[i] << endl;
	}

	return 0;
}





int main()
{
	int a[] = { 72 , 60 , 21 , 38 , 51 , 80 , 95 , 70 , 95, 60 };
	int b[102]; // a보다 더 큰 배열
	int n = 10;
	int i, j;
	int high = 101; //a 배열의 데이타 보다 더 큰수

	for (i = 0; i < high; i++)
	{
		b[i] = 0;
	}

	for (i = 0; i < n; i++)
	{
		b[a[i]]++;
	}

	b[high] = 1;

	for (i = high - 1; i >= 0; i--)
	{
		b[i] += b[i + 1];
	}


	cout << "DATA RANKING" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << "\t" << b[a[i]+1] << endl;
	}

	return 0;
}