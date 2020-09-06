#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
	int num, input;
	ifstream ii("input.txt");
	//ifstream ii("D:\\input.txt");

	ofstream oo("output.txt");
	//ofstream oo("D:\\output.txt");
	ii >> num;

	int root;
	int origin;
	int largeroot = 0;
	int largeorigin = 0;
	int temp = 0;

	for (int i = 0; i < num; i++)
	{
		root = 0;
		ii >> input;
		origin = input;
		
		while (input > 0)
		{
			root = root + input % 10;
			input = input / 10;
			if (input == 0 && root > 9)
			{
				input = root;
				root = 0;
			}
			if (input == 0 && root < 10)
			{
				break;
			}
		}
		if (root > largeroot)
		{
			largeroot = root;
			largeorigin = origin;
		}
		if (root == largeroot)
		{
			if (origin < largeorigin)
			{
				largeorigin = origin;
			}
		}
	}
	oo << largeorigin;

	ii.close();
	oo.close();
	return 0;
}