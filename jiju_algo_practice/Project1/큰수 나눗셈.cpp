#include <iostream>
#include<fstream>
#include<string>
#include <math.h>

using namespace std;
// ii >>
// oo <<
int main()
{
	string big; //97543
	string div; //11
	int abig[30];
	int temp[30];
	int i, j;
	ifstream ii("D:\\input.txt");
	//ifstream ii("input.txt");

	ofstream oo("D:\\output.txt");
	//ofstream oo("output.txt");
	getline(ii, big);
	ii >> div;
	int lbig = big.length(); // 5
	int ldiv = div.length(); //2

	int idiv = atoi(div.c_str());
	int mark = int((double(lbig) - 0.1) / ldiv);
	int m, r;
	int input;
	//배열 안에 넣기
	if (lbig % 2 == 0)	//배열이 짝수일 경우
	{
		input = 0;
		m = lbig / ldiv;  // 6/2 = 3
		for (i = 0; i < mark + 1; i++) // 0 to 2
		{
			abig[i] = atoi(big.substr(input, ldiv).c_str());
			input = input + ldiv;
		}
	}
	else //배열이 홀수일 경우
	{
		m = lbig / ldiv; // 5/2 =2
		r = lbig % ldiv; // 5%2=1
		input = r;
		abig[0] = atoi(big.substr(0, r).c_str());
		for (i = 1; i < mark + 1; i++)
		{
			abig[i] = atoi(big.substr(input, ldiv).c_str());
			input = input + ldiv;
		}
	}
	//---------------------------완료
	int answer[30];
	int surplus[30];
	int cnt = 0;
	for (i = 0; i < mark + 1; i++)
	{

		answer[i] = abig[i] / idiv;
		surplus[i] = abig[i] % idiv;
		abig[i + 1] = surplus[i] * pow(10, ldiv) + abig[i + 1];
		cnt++;
	}
	int key;
	for (i = 0; i < mark + 1; i++)
	{
		if (answer[i] != 0)
		{
			key = i;
			break;
		}
	}
	for (i = key; i < mark + 1; i++)
	{
		oo << answer[i];
		if (i == mark)
		{

		}
		oo.width(ldiv);
		oo.fill('0');
	}
	oo.width(1);

	oo << endl << surplus[cnt - 1];

	/*
	for (i = mark; i > 0; i--)
	{
		for (j = ldiv; j > -1; j--)
		{

		}
	}
	*/


	ii.close();
	oo.close();
	return 0;
}
