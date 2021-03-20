#include <iostream>
#include<fstream>
#include<string>
using namespace std;
int a, b, k, t, start, finish;
int c[100001];
int main() 
{
	//ifstream ii("D:\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("D:\\output.txt");
	ofstream oo("output.txt");
		k = 0;
		memset(c, -1, sizeof(c));

		ii >> a >> b;
		start = finish = 0;

		//printf("%d.", (a / b));
		oo << a / b;
		int temp = a % b * 10;

		while (true) 
		{ //순환되는 부분까지 찾기
			a = a % b * 10;
			if (c[a] != -1) 
			{
				start = c[a];
				finish = k;
				break;
			}
			c[a] = k++;
		}

		for (int i = 0; i < start; i++) 
		{
			//printf("%d", temp / b);
			oo << temp / b;
			temp = temp % b * 10;
		}
		printf("(");
		oo << "(";
		for (int i = start; i < finish; i++) 
		{
			//printf("%d", temp / b);
			oo << temp / b;
			temp = temp % b * 10;
		}
		oo << ")";
		printf(")\n");
	return 0;
}

