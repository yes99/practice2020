#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<

void spare();
void strike();
void normal();


int main()
{

	string spad; //21����
	ifstream ii("C:\\������\\input.txt");
	//ifstream ii("input.txt");

	ofstream oo("C:\\������\\output.txt");
	//ofstream oo("output.txt");





	getline(ii, spad);

	ii.close();
	oo.close();
	return 0;
}




void spare(int i, int score, int* spad[])
{
	score = score + 10 + spad[i + 1];
}

void strike()
{

}

void normal()
{

}