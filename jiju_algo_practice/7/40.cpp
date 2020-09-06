#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	string standard;
	string change;
	string word;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> standard;
	ii.ignore();
	ii >> change;
	ii.ignore();
	string sentence="";
	string temp;
	int flag = 0;
	for (int j = 0; j < 10000; j++)
	{
		ii >> word;
		if (word == standard)
		{
			word = change;
			flag = 1;
		}
		if (temp == word)
		{
			break;
		}
		temp = word;
		sentence = sentence + word+ " ";
	}
	if (flag == 1)
	{
		oo << sentence;
	}
	else
	{
		oo << "ERROR";
	}
	

	ii.close();
	oo.close();
	return 0;
}