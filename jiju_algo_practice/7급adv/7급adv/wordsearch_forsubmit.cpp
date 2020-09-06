#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	string sentence;
	int num;
	string word;


	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	int j; // 단어 내 스펠링 체크
	int k;// 문장 내 스펠링 체크
	int wordcnt = 0;
	int finalcnt = 0;
	getline(ii, sentence);
	string origin = sentence;
	int flag = 0;
	ii >> num;
	ii.ignore();
	for (int i = 0; i < num; i++)
	{
		getline(ii, word);
		for (j = 0; j < word.length(); j++)  // 단어체크
		{
			for (k = 0; k < sentence.length(); k++) // 문장 체크
			{
				if (word[j] == sentence[k])
				{
					wordcnt++;
					sentence.erase(k, 1);
					if (wordcnt == word.length())
					{
						finalcnt++;
						flag = 1;
						break;
					}
					break;
				}
			}
		}
		wordcnt = 0;
		sentence = origin;
	}

	oo << finalcnt;


	ii.close();
	oo.close();
	return 0;
}