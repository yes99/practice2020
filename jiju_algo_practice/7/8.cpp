#include <iostream>
#include<fstream>
#include<string>
using namespace std;
// ii >>
// oo <<
int main()
{
	int n, num;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> n;
	int cnt;
	int origin;
	int large = 0;
	int largecnt = 0;
	
	for (int i = 0; i < n; i++)
	{
		cnt = 0;
		ii >> num;
		origin = num;
		while (num > 0)
		{
			if (num % 2 == 1)
			{
				cnt++;
			}
			// 1- r % 2 ==   -> 0의 갯수 구하기
			num = num / 2;
		}
		if (cnt > largecnt)
		{
			large = origin;
			largecnt = cnt;
		}
		else if (cnt == largecnt)
		{
			if (origin < large)
			{
				large = origin;
			}
		}
	}
	oo << large;
	ii.close();
	oo.close();
	return 0;
}