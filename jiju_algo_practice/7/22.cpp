#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	double height;
	//ifstream ii("C:\\������\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\������\\output.txt");
	ofstream oo("output.txt");
	double answer;
	ii >> height;
	answer = (sqrt(5) * height - height) / 2;
	oo.setf(ios::fixed);
	oo.precision(1);
	oo << answer;
	ii.close();
	oo.close();
	return 0;
}