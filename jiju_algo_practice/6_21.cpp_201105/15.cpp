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
	string check = "";
	string standard = "AAHINORSTTUU";
	int i, j, k;
	int flag=3;
	char spelling = 'A';
	int length;
	//ifstream ii("C:\\������\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\������\\output.txt");
	ofstream oo("output.txt");
	//ii >> num; ii.ignore();
	/*
	1. �̸��� ���� �빮��ȭ;
	2. A���� �ϳ��� Ȯ��
	3. ���� �ش� ���ĺ��� ������,  ����� ����� flag 1 �ؼ� �ٽ� �� ���ĺ� ��ġ
	4. ������ flag 0 �ؼ� �����ŷ� �Ѿ. 
	6
Lui Armstrong Sebaschan
Shell Maximillian
Etaix Pierre
Giovanni Antonio Bazzi
Techrina Ludmilia
Amond Aoeria
	*/
	//���ĺ� Ž��
	ii >> num; ii.ignore();
	for (k = 0; k < num; k++)
	{
		getline(ii, name);
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
		//oo << name << "   ";
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

		oo << check << ' ';
		if (standard > check)
		{
			oo << 0;
		}
		else
		{
			oo << 1;
		}
		oo << endl;
		spelling = 'A';
		check = "";
	}
	ii.close();
	oo.close();
	return 0;
}