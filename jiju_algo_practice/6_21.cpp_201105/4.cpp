#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	string origin; // ù ����
	string insert; // �ִ� ����
	char answer[100];
	int onum; // ù ���� ����
	int inum;// �ִ� ���� ����
	int ilocation;// ��� �����ϰ� ������

	//ifstream ii("C:\\������\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\������\\output.txt");
	ofstream oo("output.txt");
	ii >> onum; ii.ignore();
	getline(ii, origin);
	ii >> inum; ii.ignore();
	getline(ii, insert);
	ii >>  ilocation;
	insert = insert + ' ';
	for (int i = 0; i < origin.length(); i++)
	{
		answer[i] = origin[i];
	}
	//oo << answer <<endl;
	int spacecnt = 0;
	int key;
	for (int i = 0; i < origin.length(); i++)
	{
		if (origin[i] == 32)
		{
			spacecnt++;
			if (spacecnt == ilocation - 1)
			{
				key = i;
				break;
			}
		}
	}
	for (int i = origin.length(); i >key; i--)
	{
		answer[i + insert.length()] = answer[i];
	}
	//oo << answer << endl;
	int j = 0;
	for (int i = 0; i < insert.length(); i++)
	{
		answer[i+key+1] = insert[i];
	}
	for (int i = 0; i < origin.length() + insert.length(); i++)
	{
		oo<< answer[i];
	}
//	oo << answer << endl;
	





	ii.close();
	oo.close();
	return 0;
}