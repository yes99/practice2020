#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	int n;
	string poet;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> n;
	ii.ignore();
	//getline(ii, poet);
	//n = atoi(poet.c_str());
	int length;
	int least = 1000000, most = 0, total=0; 
	for (int i = 0; i < n; i++)
	{
		getline(ii, poet);
		length = poet.length();
		if (length < least)
		{
			least = length;
		}
		if (length > most)
		{
			most = length;
		}
		total = total + length;
	}
	oo << most << endl << least << endl << total;

	ii.close();
	oo.close();
	return 0;
}