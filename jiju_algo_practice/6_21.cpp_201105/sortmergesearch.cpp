#include <time.h>
#include <iostream>
using namespace std;

int main()
{
	srand(time(NULL));
	int a[100];
	int b[200];
	int c[200];
	/*********배열의 준비와 정렬************/
	int i, j, k;
	int na, n, flag;
	int check[1000];
	na = rand() % 91 + 10;  //a배열의 데이터 수
	for (i = 0; i < 200; i++)
	{
		check[i] = 0; // check 배열의 clear
	}
	for (i = 0; i < na; i++)
	{
		do 
		{    //중복 데이터 제거
			n = int(rand() % 900 + 100);
		} while (check[n] != 0);
		a[i] = n;
		check[n] = 1;
	}

	for (i = 1; i < na - 1; i++)  //bubble sort
	{
		flag = 0; 
		for (j = 0; j < na - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				flag = 1;
			}

		}
		if (flag == 0)
		{
			i = na;
		}
	}

	int nb = rand() % 91 + 10; //b 배열의 데이터 수
	for (i = 0; i < 200; i++)
	{
		check[i] = 0;  // check 배열의 clear
	}
	
	for (i = 0; i < nb; i++)
	{
		do {  //중복 데이터의 제거
			n = rand() % 900 + 100;
		} while (check[n] != 0);
		b[i] = n;
		check[n] = 1;
	}

	for (i = 0; i < nb; i++)
	{
		for (j = i - 1; j >= 0; j--)
		{
			if (b[j] > b[j + 1])
			{
				int temp = b[j];
				b[j] = b[j + 1];
				b[j + 1] = temp;
			}
		}
	}
	/*****MERGE*****/
	int eps = 999;
	a[na] = eps;
	b[nb] = eps;
	i = 0; j = 0; k = 0;
	while (!(a[i] == eps && b[j] == eps))
	{
		if (a[i] < b[j])
		{
			c[k++] = b[i++];
		}
		else if (a[i] > b[j])
		{
			c[k++] = b[j++];
		}
		else if (a[i] == b[j])
		{
			c[k++] = a[i++];
			j++;
		}
	}

	for (i = 0; i < k; i++) // search 때 참고
	{
		cout.width(6);
		cout << c[i];
		if (i % 10 == 9)
		{
			cout << endl;
		}
	}
	cout << endl;
/***********binary search******************/
	int m, lower, upper;
	while (true)
	{
		cout << " 찾을 숫자는? : ";
		cin >> n;
		lower = 0; 
		upper=k;
		flag = 0;
		while (lower <= upper)
		{
			m = (lower + upper) / 2;
			if (n == c[m])
			{
				flag = 1;
				break;
			}
			if (n < c[m])
			{
				upper = m - 1;
			}
			else
			{
				lower = m + 1;
			}
		}
		if (flag == 1)
		{
			cout << n << "는(은)" << m + 1 << " 번째에 있습니다" << endl;
		}
		else
		{
			cout << n << "는 찾을수 없습니다" << endl;
		}
	}

	return 0;
}