#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	string sentence;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	getline(ii, sentence);
	int num = sentence.length();
	char word;
	char output;
	int temp , t;
	for (int i = 0; i < num; i++)
	{
		word = sentence[i];
		if (word > 64 && word < 91)
		{
			word = word + 32;
		}
		if (word > 96 && word < 123)
		{
			temp = word / 26;
			t = word % 26;
			output = t + 3 + temp * 26;
			if (output > 122)
			{
				temp = temp - 1;
				output = t + 3 + temp * 26;
			}
			oo << output;
		}
		else
		{
			oo << word;
		}
	}


	ii.close();
	oo.close();
	return 0;
}