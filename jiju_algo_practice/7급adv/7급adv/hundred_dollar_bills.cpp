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
	string word;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	int j;
	ii >> num; ii.ignore();
	int ggang=0;
	int ggangcnt=0;
	for (int i = 0; i < num; i++)
	{
		getline(ii, word);
		for (j = 0; j < word.length(); j++)
		{
			ggang = ggang + (word[j] - 96);
		}
		if (ggang == 100)
		{
			ggangcnt++;
		}
		ggang = 0;
	}

	oo << ggangcnt;
	ii.close();
	oo.close();
	return 0;
}