#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	int rand;
	int n;
	int small, large;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> rand >> n;

	for (int i = 0; i < n; i++)
	{
		ii >> small >> large;
	
		if (rand >= small  && rand <= large)
		{
			oo << "까치발" << endl;
		}
		else if (rand <= small)
		{
			oo << "너무 큼" << endl;
		}
		else if ( rand >= large)
		{
			oo << "너무 작음" << endl;
		}
	}

	ii.close();
	oo.close();
	return 0;
}