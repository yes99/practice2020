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
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	//ii >> num; ii.ignore();
	/*
	1. 이름을 전부 대문자화;
	2. A부터 하나씩 확인
	3. 만약 해당 알파벳이 있으면,  출력후 지우고 flag 1 해서 다시 그 알파벳 서치
	4. 없으면 flag 0 해서 다음거로 넘어감. 
	6
Lui Armstrong Sebaschan
Shell Maximillian
Etaix Pierre
Giovanni Antonio Bazzi
Techrina Ludmilia
Amond Aoeria
	*/
	//알파벳 탐색
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