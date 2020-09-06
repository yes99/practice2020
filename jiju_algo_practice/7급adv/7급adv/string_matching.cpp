#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	string word;
	string sentence;

	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> word;
	ii.ignore();
	int cnt = 0;
	int length = word.length();
	getline(ii, sentence);
	for (int j = 0; j < sentence.length(); j++)
	{
		if (sentence.substr(j, length) == word)
		{
			oo << j + 1;
			break;
		}
	}

	ii.close();
	oo.close();
	return 0;
}