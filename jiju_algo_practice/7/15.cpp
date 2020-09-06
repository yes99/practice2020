#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	int n;
	int a, x, b, m;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> n;
	ii >> a >> x >> b >> m;
	int answer;
	for (int i = 0; i < n; i++)
	{
		x = (a * x + b) % m;
	}
	oo << x;
	ii.close();
	oo.close();
	return 0;
}