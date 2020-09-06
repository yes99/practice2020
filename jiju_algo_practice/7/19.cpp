#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	int num;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> num;

	int temp;
	temp = num + num / 1000;
	int tt;
	tt = temp + (temp * 10000) % 1000000;
	int ttt;
	ttt = tt % 100;

	oo << ttt;
	ii.close();
	oo.close();
	return 0;
}