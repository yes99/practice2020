#include <iostream>
#include<fstream>
#include<string>
#include<math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int key;
	string normal;
	string cipher;
	char ck;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");
	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii>> key;
	ii.ignore();
	getline(ii, normal);
	int num = normal.length();
	int i, j;
	for (i = 0 ; i <num ; i++)
	{
		if(normal[i] >96 && normal[i] < 123)
		{
			normal[i] = normal[i] - 32;
		}
	}
	int code;
	for(j = 0; j < num ; j++)
	{
		if(normal[j] > 64 && normal[j] < 91)
		{
			key = key * key;
			key = key % 1000;
			code= key / 100;
			ck = normal[j] + code;
			if(ck > 90)
			{
				ck = (ck - 65) % 26 + 65;
			}
			cipher = cipher + ck;
		}
		else
		{
			cipher = cipher + normal[j];
		}
	}

	oo << cipher;
	ii.close();
	oo.close();
	return 0;
}
