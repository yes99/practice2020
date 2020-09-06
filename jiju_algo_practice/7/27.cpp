#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	double ys;
	double a, b;
	ifstream ii("C:\\이현석\\input.txt");
	//ifstream ii("input.txt");

	ofstream oo("C:\\이현석\\output.txt");
	//ofstream oo("output.txt");
	ii >> a >> b;
	int cnt=0;
	double first, last=150 , temp=0;
	for (double i = 0; i <= 6.4; i += 0.01)
	{
		ys = 30 * sin(a*i)*cos(b*i) + 150;
		first = last;
		last = ys;
		if (temp > 0 && last - first <0)
		{
			cnt++;
		}
		temp = last - first;
	}



	oo << cnt;
	ii.close();
	oo.close();
	return 0;
}