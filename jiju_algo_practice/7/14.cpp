#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	int marble, num, time;
	ifstream ii("C:\\������\\input.txt");
	//ifstream ii("input.txt");

	ofstream oo("C:\\������\\output.txt");
	//ofstream oo("output.txt");
	ii >> marble >> num >> time;

	oo << ((num*(time-1)+1));


	ii.close();
	oo.close();
	return 0;
}