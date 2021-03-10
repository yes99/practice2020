#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	string origin; // 첫 문장
	string insert; // 넣는 문장
	char answer[100];
	int onum; // 첫 문장 길이
	int inum;// 넣는 문장 길이
	int ilocation;// 어디 삽입하고 싶은지

	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
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