#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	int big, small;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> big >> small;
	int gcd;
	for (int i = 1; i < small + 1; i++)
	{
		if (big % i == 0 && small % i == 0)
		{
			gcd = i;
		}
	}

	oo << big / gcd << " " << small / gcd;
	ii.close();
	oo.close();
	return 0;
}