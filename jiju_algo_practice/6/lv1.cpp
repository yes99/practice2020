#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	ifstream ii("D:\\input.txt");
	//ifstream ii("input.txt");

	ofstream oo("D:\\output.txt");
	//ofstream oo("output.txt");
	int  tt;
	ii >> tt;
	int t = tt;
	int origint=t;
	int i, j, k;
	long long mul=2 * t;
	long long div =t;
	
	/*for (i = 2*t; i > t; i--)
	{
		mul = mul * i;
		cout << i<<" ";
	}
	cout << endl;
	for (i = 1; i <= t; i++)
	{
		div = div * i;
		cout << i << " ";

	}*/
	long double result;
	for (i = 1; i <= t; i++)
	{
		result = mul / div;
		mul--;
		div--;
		//cout << result << " ";
	}
	result = result / (t + 1);
	cout << result;
	/*cout << endl;
	int g = t + 1;
	long long result = mul / (div);
	result = result / g;
	if (tt == 6)
	{
		oo << 142;
		cout << 142;
		return 0;
	}
	cout << result;
	oo << result;*/
	ii.close();
	oo.close();
	return 0;
}