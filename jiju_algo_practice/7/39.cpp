#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	string standard;
	int num;
	string sentence;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> standard;
	ii.ignore();
	ii >> num;
	ii.ignore();
	string temp;
	int cnt = 0;
	for (int i = 0; i < num; i++)
	{
		getline(ii, sentence);
		for (int j = 0; j < sentence.length(); j++)
		{
			if (sentence.substr(j  ,  standard.length()) == standard)
			{
				cnt++;
			}
		}
	}

	oo << cnt;


	ii.close();
	oo.close();
	return 0;
}