#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	int a, m;
	int num;
	int b;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> a >> m >> num;
	int mod;
	mod = a % m;
	int cnt = 0;
	for (int i = 0; i < num; i++)
	{
		ii >> b;
		if (b % m == mod)
		{
			cnt++;
		}
	}

	oo << cnt;
	ii.close();
	oo.close();
	return 0;
}