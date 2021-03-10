#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	string alpha;
	int num;

	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	getline(ii, alpha);
	ii >> num;
	int length = alpha.length();
	char answer[100];
	if (num > 0) //right
	{
		for (int i = 0; i < alpha.length(); i++)
		{
			answer[(i + num) % length] = alpha[i];
		}
	}
	else// left
	{
		num = length + num;
		for (int i = 0; i < alpha.length(); i++)
		{
			answer[(i + num) % length] = alpha[i];
		}
	}
	for (int i = 0; i < length; i++)
	{
		oo << answer[i];
	}

	ii.close();
	oo.close();
	return 0;
}