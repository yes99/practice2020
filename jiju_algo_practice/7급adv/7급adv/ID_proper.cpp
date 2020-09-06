#include <iostream>
#include<fstream>
#include<string>
#include<math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	string id;
	ifstream ii("D:\\input.txt");
	//ifstream ii("input.txt");

	ofstream oo("D:\\output.txt");
	//ofstream oo("output.txt");
	getline(ii, id);
	char word;
	int num = id.length();
	for (int i = 0; i < num; i++)
	{

	}



	ii.close();
	oo.close();
	return 0;
}