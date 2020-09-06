#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{

	int f, s, t;
	int total;
	int inputmoney;
	int pull;

	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");

	ii >> f >> s >> t >> total >> inputmoney >> pull;
	int origin = inputmoney;
	int plus;
	int all = inputmoney + total;
	for (int i = 0; i <pull; i++)
	{
		inputmoney = inputmoney - 10;
		total = total + 10;
		f = (((f * 1234) + 8) * ((f * 1234) + 8) - 7) % 10;
		s = (((s * 1234) + 8) * ((s * 1234) + 8) - 7) % 10;
		t = (((t * 1234) + 8) * ((t * 1234) + 8) - 7) % 10;
		//if (f == s == t)
		if(f==s && s == t && t == f)
		{
			if ((total / 2) % 10 != 0)
			{
				plus = total / 2 + 5;
			}
			else
			{
				plus = total / 2;
			}
			inputmoney = inputmoney + plus;
			total = all - inputmoney;
		}
		if (inputmoney == 0)
		{
			break;
		}
	}

	oo << inputmoney - origin;

	ii.close();
	oo.close();
	return 0;




}