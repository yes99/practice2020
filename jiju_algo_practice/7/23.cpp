#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	int stair, up, down;
	//ifstream ii("C:\\������\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\������\\output.txt");
	ofstream oo("output.txt");
	ii >> stair >> up >> down;
	double answer;
	answer = 2 * stair / (up + down);
	oo.setf(ios::fixed);
	oo.precision(2);
	oo << answer;

	ii.close();
	oo.close();
	return 0;
}