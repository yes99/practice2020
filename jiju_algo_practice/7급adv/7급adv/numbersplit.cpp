#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{

	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	char id;
	for (int i = 0; i < 7; i++)
	{
		ii >> id;
		oo << id - 48 << endl;
	}


	ii.close();
	oo.close();
	return 0;
}