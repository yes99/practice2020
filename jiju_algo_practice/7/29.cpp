#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	//ifstream ii("C:\\������\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\������\\output.txt");
	ofstream oo("output.txt");
	oo << "D";
	ii.close();
	oo.close();
	return 0;
}