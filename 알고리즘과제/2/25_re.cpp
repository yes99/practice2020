#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<

void sort(string a[], int n)
{
	int i, j;
	string t;
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

}


int main()
{
	int prg, ord;
	string program;
	string order;
	string orderprogram;
	string parray[10000];
	string oarray[10000];
	int i, j, k;
	int flag = 0, flag1 = 0, flag2 = 0;

	ifstream ii("C:\\이현석\\input.txt");
	//ifstream ii("input.txt");

	ofstream oo("C:\\이현석\\output.txt");
	//ofstream oo("output.txt");
	ii >> prg >> ord; 
	for (i = 0; i < prg; i++)
	{
		ii >> program;
		parray[i] = program;
	}

	for (i = 0; i < ord; i++)
	{
		ii >> order >> orderprogram;

		if (order == "Make")
		{
			parray[prg] = orderprogram;
			oo << "OK" << endl;;
			prg = prg + 1;
		}
		else if (order == "Delete")
		{
			for (j = 0; j < prg; j++)
			{
				int tempj;
				if (parray[j] == orderprogram)
				{
					flag = 1;
					oo << "OK" << endl;
					tempj = j;
					for (k = 0; k < prg - j - 1; k++)
					{
						parray[tempj] = parray[tempj + 1];
						tempj++;
					}
					parray[prg - 1] = "";
					prg = prg - 1;
				}
			}
			if (flag == 0)
			{
				oo << "Not found" << endl;
			}
		}
		else //search
		{
			sort(parray, prg); // 소팅 아마...
			string file = oarray[i * 2 + 1];
			int l = file.length();
			if (oarray[i * 2 + 1].substr(0, 1) == "*") // 전체 찾는건지?
			{
				oo << oarray[i * 2] << " " << oarray[i * 2 + 1] << endl;;
				for (j = 0; j < prg; j++)
				{
					flag1 = 1;
					if (parray[j].find(file.substr(l - 3, l)) != string::npos) // 검색해서 널값이 아니면
					{
						oo << parray[j] << endl;
					}
				}
				if (flag1 == 0)
				{
					oo << "Not found" << endl;
				}
			}
			else // 특정 검색인지?
			{
				oo << oarray[i * 2] << " " << oarray[i * 2 + 1] << endl;;
				for (j = 0; j < prg; j++)
				{
					if (parray[j] == oarray[i * 2 + 1])
					{
						flag2 = 1;
						oo << oarray[i * 2 + 1];
						break;
					}
				}
				if (flag2 == 0)
				{
					oo << "Not found" << endl;
				}
			}
		}
		flag = 0, flag1 = 0, flag2 = 0;
	}
	for (i = 0; i < prg; i++)
	{
		cout << parray[i] << endl;
	}

	ii.close();
	oo.close();
	return 0;
}