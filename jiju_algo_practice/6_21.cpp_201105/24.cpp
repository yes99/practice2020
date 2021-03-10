#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
#include <algorithm>
using namespace std;
// ii >>
// oo <<
struct info
{
	int id;
	double length;
	int count;
	double weight;
};
struct ranking
{
	int id;
	double allr;
	int score;
};

int main()
{
	info a[100];
	ranking r[100];
	int number;
	int id;
	double length;
	int count;
	double weight;
	double totalr[100] = { 0, };
	int rank[100];
	double t;
	/*int ida[1000];
	double lengtha[1000];
	int counta[1000];
	double weighta[1000];
	*/
	int i, j, k;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> number;
	for (i = 0; i < number; i++)
	{
		ii >> id >> length >> count >> weight;
		a[i].id = id;
		a[i].length = length;
		a[i].count = count;
		a[i].weight = weight;
		r[i].id = id;
		r[i].score = i + 1;
	}

	for (i = 0; i < number; i++)
	{
		rank[i] = 1;
	}

	for (i = 0; i < number-1; i++)
	{
		for (j = i + 1; j < number; j++)
		{
			if (a[i].length < a[j].length)
			{
				rank[i]++;
			}
			else if (a[i].length > a[j].length)
			{
				rank[j]++;
			}
		}
	}

	//for (i = 0; i < number; i++)
	//{
	//	cout << rank[i] << " ";
	//}
	for (i = 0; i < number; i++)
	{
		totalr[i] = totalr[i] + rank[i];
	}
	for (i = 0; i < number; i++)
	{
		rank[i] = 1;
	}
	//cout << endl;

	for (i = 0; i < number - 1; i++)
	{
		for (j = i + 1; j < number; j++)
		{
			if (a[i].count < a[j].count)
			{
				rank[i]++;
			}
			else if (a[i].count > a[j].count)
			{
				rank[j]++;
			}
		}
	}

	//for (i = 0; i < number; i++)
	//{
	//	cout << rank[i] << " ";
	//}
	for (i = 0; i < number; i++)
	{
		totalr[i] = totalr[i] +rank[i];
	}
	for (i = 0; i < number; i++)
	{
		rank[i] = 1;
	}
	//cout << endl;




	for (i = 0; i < number - 1; i++)
	{
		for (j = i + 1; j < number; j++)
		{
			if (a[i].weight < a[j].weight)
			{
				rank[i]++;
			}
			else if (a[i].weight > a[j].weight)
			{
				rank[j]++;
			}
		}
	}

	//for (i = 0; i < number; i++)
	//{
	//	cout << rank[i] << " ";
	//}
	for (i = 0; i < number; i++)
	{
		totalr[i] = totalr[i] + rank[i];
	}
	//cout << endl;
	//for (i = 0; i < number; i++)
	//{
	//	cout << totalr[i] << " ";
	//}


	for (i = 0; i < number - 1; i++)
	{
		for (j = i + 1; j < number; j++)
		{
			if (totalr[i] == totalr[j])
			{
				if (a[i].length > a[j].length)
				{
					totalr[j] = totalr[j] + 0.1;

				}
				else
				{
					totalr[i] = totalr[i] + 0.1;

				}
			}
		}
	}
	//cout << endl;
	for (i = 0; i < number; i++)
	{
		r[i].allr = totalr[i];
		//cout << totalr[i] << " ";
	}


	//cout << endl;
	//for (i = 0; i < number; i++)
	//{
	//	cout << r[i].id << " " << r[i].allr << endl;
	//}

	//
	//cout << endl;
	for (i = 1; i <= number - 1; i++)
	{
		for (j = 0; j < number - i; j++)
		{
			if (r[j].allr > r[j + 1].allr)
			{
			ranking	t = r[j];
				r[j] = r[j+1];
				r[j+1] = t;
			}
		}
	}
	//cout << endl;
	for (i = 0; i < number; i++)
	{
		r[i].score = i + 1;
		//cout <<r[i].score<< " " <<r[i].id <<" " <<r[i].allr << endl;
	}


	for (i = 1; i <= number - 1; i++)
	{
		for (j = 0; j < number - i; j++)
		{
			if (r[j].id > r[j + 1].id)
			{
				ranking t = r[j];
				r[j] = r[j + 1];
				r[j + 1] = t;
			}
		}
	}
	//cout << endl;
	//for (i = 0; i < number; i++)
	//{
	//	cout << r[i].score << " " << r[i].id << " " << r[i].allr << endl;
	//}
	//cout << endl;


	for (i = 0; i < number; i++)
	{
		oo << r[i].id << " " << r[i].score << endl;
	}
	ii.close();
	oo.close();
	return 0;
}