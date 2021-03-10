#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int count;
	int num;
	int au[100];
	int aa[100];
	int ab[100];
	int i, j, k;
	int t;
	int nu=0, na=0, nb=0;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");

	ii >> count;
	for (i = 0; i < count; i++)
	{
		ii >> num;
		au[i] = num;
		nu++;
	} // U 
	ii >> count;
	for (i = 0; i < count; i++)
	{
		ii >> num;
		aa[i] = num;
		na++;
	} // A 
	ii >> count;
	for (i = 0; i < count; i++)
	{
		ii >> num;
		ab[i] = num;
		nb++;
	} // B 

	int bigger = na > nb ? na : nb;
	int smaller = na < nb ? na : nb;

	int sum[100];
	int same[100];
	int minus[100];
	int Ac[100];
	int Bc[100];
	//sum
	int n = 0;
	for (i = 0; i < na; i++)
	{
		sum[n++] = aa[i];
	}
	int flag = 0;
	for (i = 0; i < nb; i++)
	{
		for (j = 0; j < na; j++)
		{
			if (aa[j] == ab[i])
			{
				flag = 0;
				break;
			}
			flag = 1;
		}
		if (flag == 1)
		{
			sum[n++] = ab[i];
			flag = 0;
		}
	} // U 소팅 이전까지 완료

	for (i = 1; i < n; i++)
	{
		for (j = i - 1; j >= 0; j--)
		{
			if (sum[j] > sum[j + 1])
			{
				t = sum[j];
				sum[j] = sum[j + 1];
				sum[j + 1] = t;
			}
			else
			{
				break;
			}
		}
	}
	//소팅도 완료
	if (n == 0)
	{
		oo << "0";
	}
	else
	{
		for (i = 0; i < n; i++)
		{
			oo << sum[i] << " ";
		}
	}
	oo << endl;
	// 공집합 계산 ㄱ
	n = 0;
	for (i = 0; i < smaller; i++)
	{
		for (j = 0; j < bigger; j++)
		{
			if (aa[i] == ab[j])
			{
				same[n] = aa[i];
				n++;
				break;
			}
		}
	}
	if (n == 0)
	{
		oo << "0";
	}
	else
	{
		for (i = 0; i < n; i++)
		{
			oo << same[i] << " ";
		}
	}
	oo << endl;
	//공집합 소팅 이전까지 완료

	//차집합
	flag = 1;
	int nm = 0;
	for (i = 0; i < na; i++)
	{
		for (j = 0; j < nb; j++)
		{
			if (aa[i] == ab[j])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			minus[nm] = aa[i];
			nm++;
		}
		flag = 1;
	}
	if (nm == 0)
	{
		oo << "0";
	}
	else
	{
		for (i = 0; i < nm; i++)
		{
			oo << minus[i] << " ";
		}
	}
	oo << endl;
	// 차도 대충 완료
	
	//A의 여집합
	flag = 0;
	n = 0;
	for (i = 0; i < nu; i++)
	{
		for (j = 0; j < na; j++)
		{
			if (au[i] == aa[j])
			{
				n++;
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			Ac[i] = au[i];
			oo << Ac[i] << " ";
		}
		flag = 0;
	}
	if (nu - n == 0)
	{
		oo << "0";
	}
	oo << endl;

	//B의 여집합
	flag = 0;
	n = 0;
	for (i = 0; i < nu; i++)
	{
		for (j = 0; j < nb; j++)
		{
			if (au[i] == ab[j])
			{
				n++;
				flag = 1;
				break;
			}
		}
		if (flag == 0) 
		{
			Bc[i] = au[i];
			oo << Bc[i] << " ";
		}
		flag = 0;
	}
	if (nu - n == 0)
	{
		oo << "0";
	}
	oo << endl;



	ii.close();
	oo.close();
	return 0;
}