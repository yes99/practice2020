#include <iostream>
#include<fstream>
#include<string>
#include<math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	string sentence;
	int num;
	string word;
	string origin;

	ifstream ii("C:\\이현석\\input.txt");
	//ifstream ii("input.txt");
	ofstream oo("C:\\이현석\\output.txt");
	//ofstream oo("output.txt");
	
	getline(ii, sentence);
	ii>> num;
	ii.ignore();
	int i , j , k;
	int l;
	int maincnt=0;
	int minorcnt = 0;
	int allnum = sentence.length();
	for(i = 0 ; i < num; i++)
	{
		getline(ii, word);
		l = word.length();
		for(k = 0; k <l ; k++)
		{
			for(j =0 ; j< allnum; j++)
			{
				if(sentence[j] == word[k])
				{
					sentence.erase(j,1);
					minorcnt++;
					j = 0;
					allnum = sentence.length();
				}
				if(minorcnt == l)
				{
					maincnt++;
					break;
				}
		}
		sentence = origin;
	}

	oo << maincnt;
	ii.close();
	oo.close();
	return 0;
}
}


			
	/*	for(j =0 ; j< allnum; j++)
		{
			for( k =0 ; k < l ; k++)
			{
				if(sentence[j] == word[k])
				{
					sentence.erase(j,1);
					minorcnt++;
					j = 0;
					allnum = sentence.length();
				}
				if(minorcnt == l)
				{
					maincnt++;
					break;
				}
			}
		
		}*/