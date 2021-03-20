#include <iostream>
#include<fstream>
#include<string>
using namespace std;

//정답임  조합 구하는거
// ii >>
// oo <<
int combination(int n, int r) {

	if (n == r || r == 0)
	{
		return 1;
	}

	// nCr = (n-1)C(r-1) + (n-1)C(r)
	return combination(n - 1, r - 1) + combination(n - 1, r);

}


int main()
{
	//ifstream ii("D:\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("D:\\output.txt");
	ofstream oo("output.txt");
	int num;
	ii >> num;
	int answer;
	answer = combination(2 * num, num) / (num + 1);

	oo << answer;

	
	ii.close();
	oo.close();
	return 0;
}