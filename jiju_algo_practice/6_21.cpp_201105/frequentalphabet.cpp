#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int alphabet[26] = { 0, };
	int num;
	string word;
	int i, j, k;
	int length;
	int key;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> num; ii.ignore();

	for (k = 0; k < num; k++)
	{
		getline(ii, word);
		for (i = 0; i < word.length(); i++)
		{
			if (word[i] > 96 && word[i] < 123)
			{
				word[i] = word[i] - 32;
			}
			else if (word[i]<65 || word[i]>122)
			{
				word.erase(i, 1);
				i--;
			}
			else if (word[i] > 90 && word[i] < 97)
			{
				word.erase(i, 1);
				i--;
			}
		}
		length = word.length();
		//oo << word << endl;
		for (i = 0; i < length; i++)
		{
			key = word[i] - 65;
			alphabet[key]++;
		}
	}
	int max= alphabet[0];
	for (i = 1; i < 26; i++)
	{
		if (max < alphabet[i])
		{
			max = alphabet[i];
		}
	}
	oo << max;
	ii.close();
	oo.close();
	return 0;
}