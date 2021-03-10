#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int num;
	double score;
	double height;
	double scoreA[1000];
	double heightA[1000];
	int need;
	int i, j, k;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> num;
	for (i = 0; i < num; i++)
	{
		ii >> score;
		ii >> height;
		scoreA[i] = score;
		heightA[i] =  height;
	}
	ii >> need;
	double t;
	int s;
	for (i = 0; i < num-1; i++)
	{
		s = i;
		for (j = i + 1; j < num; j++)
		{
			if (scoreA[s] < scoreA[j])
			{
				s = j;
			}
		}
		t = scoreA[i];
		scoreA[i] = scoreA[s];
		scoreA[s] = t;
		t = heightA[i];
		heightA[i] = heightA[s];
		heightA[s] = t;
	}
	
	/*for (i = 0; i < need; i++)
	{
		oo << scoreA[i] << " " << heightA[i] << endl;
	}*/

	double sum= 0.0;
	for (i = 0; i < need; i++)
	{
		sum = sum + heightA[i];
	}
	oo <<int( sum);
	ii.close();
	oo.close();
	return 0;
}