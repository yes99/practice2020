#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	int n;
	int y, m, d;
	//ifstream ii("C:\\������\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\������\\output.txt");
	ofstream oo("output.txt");
	ii >> n;
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		ii >> y >> m >> d;
		if ((y + (y / 4) - (y / 100) + (y / 400) + int (2.6*m + 1.6) + d) % 7 == 0)
		{
			cnt++;
		}
	}
	oo << cnt;

	ii.close();
	oo.close();
	return 0;
}