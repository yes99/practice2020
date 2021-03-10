#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int num;
	string name;
	int length;
	int i, j, k;
	string t;
	int flag = 3;
	char spelling = 'A';
	string check = "";
	string originA[1000];
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> num; ii.ignore();
	string numA[1000];
	for (k = 0; k < num; k++)
	{
		getline(ii, name);
		originA[k] = name;
		for (i = 0; i < name.length(); i++)
		{
			if (name[i] > 96 && name[i] < 123)
			{
				name[i] = name[i] - 32;
			}
			else if (name[i]<65 || name[i]>122)
			{
				name.erase(i, 1);
				i--;
			}
			else if (name[i] > 90 && name[i] < 97)
			{
				name.erase(i, 1);
				i--;
			}
		}
		length = name.length();
		for (i = 0; i < length + 1; i++)
		{

			if (name[i] == spelling)
			{
				check = check + name[i];
				name.erase(i, 1);
				i = -1;
				flag = 1;
			}
			else if (flag == 0)
			{
				spelling++;
				flag = 1;
				i = -1;
			}
			else if (i == length - 1)
			{
				flag = 0;
				i = -1;
			}
			length = name.length();
		}

		numA[k] = check;
		spelling = 'A';
		check = "";
	}
	
	for (i = 0; i < num-1; i++)
	{
		for (j = i + 1; j < num; j++)
		{
			if(numA[i]>numA[j])
			{
				t = numA[i];
				numA[i] = numA[j];
				numA[j] = t;
				t = originA[i];
				originA[i] = originA[j];
				originA[j] = t;
			}
		}
	}
	
	for (i = 0; i < num; i++)
	{
		oo << originA[i] << endl;
	}

	ii.close();
	oo.close();
	return 0;
}