#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	int n;
	string word;
	//ifstream ii("C:\\������\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\������\\output.txt");
	ofstream oo("output.txt");
	string temp;
	int cnt=0;
	for (int i = 0; i < 30000; i++)
	{
		ii >> word;
		cnt++;
		if (word == temp)
		{
			break;
		}
		temp = word;
	}
	oo << cnt-1;
	ii.close();
	oo.close();
	return 0;
}