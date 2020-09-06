#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	int exp;
	int num;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> exp;
	int expect = exp /6;
	int up;
	int upsum = 0;
	for (int i = 0; i < 6; i++)
	{
		ii >> num;
		up = (expect - num) *(expect - num);
		upsum = upsum + up;
	}
	double answer = upsum / expect;
	if (answer < 15.086)
	{
		oo << "OK";
	}
	else
	{
		oo << "NG";
	}
	ii.close();
	oo.close();
	return 0;
}