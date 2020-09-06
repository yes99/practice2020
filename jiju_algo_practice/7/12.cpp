#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	int cloud;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	int cnt = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			ii >> cloud;
			if (cloud == 1)
			{
				cnt++;
			}
		}
	}
	int answer;
	answer = (cnt + 5) / 10;
	oo << answer;



	ii.close();
	oo.close();
	return 0;
}