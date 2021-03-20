#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int Fi(int num)
{

	if (num == 1)
		return 1;
	else if (num == 2)
		return 2;
	else
		return Fi(num - 1) + Fi(num - 2);

}

int main()
{
	//ifstream ii("D:\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("D:\\output.txt");
	ofstream oo("output.txt");
	int num;
	ii >> num;

	cout << Fi(num);
	oo << Fi(num);

	ii.close();
	oo.close();
	return 0;
}