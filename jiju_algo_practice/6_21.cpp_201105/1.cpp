#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int num;
	int begin, end;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> num >> begin >> end;
	int array[20];
	int answer = 1;
	for (int i = 0; i < begin; i++)
	{
		answer = answer * 2;
	}
	//array[begin] = answer;
	for (int j = begin; j < end+1; j++)
	{
		array[j] = answer;
		oo << answer << " ";
		answer = answer * 2;
	}

	



	ii.close();
	oo.close();
	return 0;
}