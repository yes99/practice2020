
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//ii >>
//oo <<
int main()
{
	double first, max, missile, rocket, machinegun;
	ifstream ii("input.txt");
	//ifstream ii("D:\\input.txt");

	ofstream oo("output.txt");
	//ofstream oo("D:\\output.txt");
	ii >> first >> max >> missile >> rocket >> machinegun;
	double weight = max - first;

	int M = weight / missile;
	int R = (weight - M * missile) / rocket;
	int Ma = (weight - M * missile - R * rocket) / machinegun;

	oo << M << " " << R << " " << Ma;

	ii.close();
	oo.close();
	return 0;
}