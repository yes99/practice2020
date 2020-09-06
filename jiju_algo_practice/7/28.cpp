#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	double x, y;
	int a, b, c, d, e;
	float dis, total = 0.0;

	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");

	ii >> a >> b >> c >> d >> e;
	double fx = b, fy = 150;

	for (double i = 0; i <= 6.4; i += 0.01)
	{
		x = i * a + b;
		y = c * sin(d * i)*cos(e * i) + 150;
		dis = sqrt((fx - x)*(fx - x) + (fy - y)*(fy - y));
		total = total + dis;
		fx = x;
		fy = y;
	}
	//oo << total << endl;
	//int answer = total;
	//oo << answer<<endl;
	total = int(total / 10 + 0.5) * 10;
	oo << total;

	ii.close();
	oo.close();
	return 0;
}