#include <iostream>
#include<fstream>
#include<string>
#include <cmath>
using namespace std;
// ii >>
// oo <<
int main()
{
	int n;
	int number;
	double average;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> n;
	double total = 0;
	for (int i = 0; i < n; i++)
	{
		ii >> number >> average;
		total = total + average;
	}
	oo.precision(3);
	double realaverage = total / n;     //0.256888888888
	ii.close();

	//ifstream iii("C:\\이현석\\input.txt");
	ifstream iii("input.txt");
	iii >> n;

	double smallest = 1000000000, diff;
	int smallnum;
	double realdiff;
	for (int i = 0; i < n; i++)
	{
		iii >> number >> average;
		diff = realaverage - average;
		realdiff = abs(diff);
		if (realdiff < smallest)
		{
			smallest = realdiff;
			smallnum = number;
		}
	}
	oo << smallnum;
	
	
	return 0;
}