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
	//ifstream ii("C:\\������\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\������\\output.txt");
	ofstream oo("output.txt");
	ii >> rand >> n;

	for (int i = 0; i < n; i++)
	{
		ii >> small >> large;
	
		if (rand >= small  && rand <= large)
		{
			oo << "��ġ��" << endl;
		}
		else if (rand <= small)
		{
			oo << "�ʹ� ŭ" << endl;
		}
		else if ( rand >= large)
		{
			oo << "�ʹ� ����" << endl;
		}
	}

	ii.close();
	oo.close();
	return 0;
}