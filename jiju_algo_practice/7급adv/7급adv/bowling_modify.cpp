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

	string spad; //21개얌
	ifstream ii("C:\\이현석\\input.txt");
	//ifstream ii("input.txt");

	ofstream oo("C:\\이현석\\output.txt");
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