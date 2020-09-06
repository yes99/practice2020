#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	int length, num, input;
	int cnt = 0;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> length >> num;
	int leftover = 0;
	for (int i = 0; i < num; i++)
	{
		ii >> input;
		cnt = cnt + (input / length);
		leftover = leftover + (input % length);
	}

	oo << cnt << endl;
	oo << leftover;

	ii.close();
	oo.close();
	return 0;
}