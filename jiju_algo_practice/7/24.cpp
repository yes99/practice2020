#include <iostream>
#include<fstream>
#include<string>
#include<math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int n;
	double x, y;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> n;
	double total= 0;
	double length;
	double temp;
	for (int i = 0; i < n; i++)
	{
		ii >> x >> y;
		temp =  (x*x + y*y);
		length = floor(sqrt(temp)*100)/100;
		total = total + length;
	}
	//double answer = total / n;
	double answer = floor((total / n)*100)/100;
	oo.setf(ios::fixed);
	oo.precision(2);
	oo << answer;

	ii.close();
	oo.close();
	return 0;
}