#include <iostream>
#include<fstream>
#include<string>
using namespace std;

//정답임 로마 숫자 더하기
// ii >>
// oo <<
int alph(char a)
{
	if (a == 'M')
	{
		return 1000;
	}
	else if (a == 'D')
	{
		return 500;
	}
	else if (a == 'C')
	{
		return 100;
	}
	else if (a == 'L')
	{
		return 50;
	}
	else if (a == 'X')
	{
		return 10;
	}
	else if (a == 'V')
	{
		return 5;
	}
	else
	{
		return 1;
	}
}




int main()
{
	//ifstream ii("D:\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("D:\\output.txt");
	ofstream oo("output.txt");
	int num[1000];
	string rom;
	int n;
	int i, j, k;
	int z;
	int answer = 0;
	ii >> n;
	for (z = 0; z < n; z++)
	{
		ii >> rom;
		int l = rom.length();

		for (i = 0; i < l; i++)
		{
			num[i] = alph(rom[i]);
		}
		int result = 0;
		int prev = 0;
		for (i = l - 1; i >= 0; i--)
		{
			if (num[i] < prev)
			{
				result -= num[i];
			}
			else
			{
				result += num[i];
				prev = num[i];
			}
		}
		cout << result << endl;
		answer = answer + result;
	}
	
	cout << answer;
	oo << answer;

	ii.close();
	oo.close();
	return 0;
}