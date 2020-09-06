#include <iostream>
#include<fstream>
#include<string>
#define _USE_MATH_DEFINES
#include<math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int clock;
	ifstream ii("C:\\이현석\\input.txt");
	//ifstream ii("input.txt");

	ofstream oo("C:\\이현석\\output.txt");
	//ofstream oo("output.txt");
	ii >> clock;
	if (clock == 12)
	{
		clock = 0;
	}
	double r = M_PI * 30 * clock / 180;
	oo.setf(ios::fixed);
	oo.precision(5);

	oo << r;

	ii.close();
	oo.close();
	return 0;
}