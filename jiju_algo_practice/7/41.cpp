#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	/*string fir = id.substr(0, 6);
	string las = id.substr(7, 6);
	int first = atoi(fir.c_str());
	int last = atoi(las.c_str());*/

	//int a, b, c, d, e, f, g, h, i, j, k, l,m;
	char id;
	int sum=0;
	int flag = 0;
	int mod;
	for (int i = 0; i < 12; i++)
	{
		ii >> id;
		if (id == '-')
		{
			i = -1;
			flag = 1;
		}
		mod = i % 9+1;
		sum = sum + ( id - 48)* mod;
		if (flag ==1)
		{
			i = 5;
			flag = 0;
		}
	}
	int a = sum % 11;
	int b = a % 10;
	ii >> id;
	if (id-48 == b)
	{
		oo << 1;
	}
	else
	{
		oo << 0;
	}
	
	/*a = first / 100000;
	b = (first % 100000) / 10000;
	c = (first % 10000) / 1000;
	d = (first % 1000) / 100;
	e = (first % 100) / 10;
	f = first % 10;

	g = last / 1000000;
	h= (last % 1000000) / 100000;
	i = (last % 100000) / 10000;
	j = (last % 10000) / 1000;
	k = (last % 1000) / 100;
	l = (last % 100)/10;
	m = last % 10;
	*/
	/*int x;
	x = a * 1 + b * 2 + c * 3 + d * 4 + e * 5 + f * 6 + g * 7 + h * 8 + i * 9 + j * 1 + k * 2 + l * 3;
	int y;
	y = x % 11;
	int z; 
	z = x % 10;
	if (z == m)
	{
		oo << 1;
	}
	else if(z != m)
	{
		oo << 0;
	}
	else if (last/1000000 ==0)
	{
		oo << " ";
	}
	*/
	ii.close();
	oo.close();
	return 0;
}