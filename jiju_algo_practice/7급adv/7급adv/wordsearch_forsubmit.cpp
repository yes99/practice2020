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


	//ifstream ii("C:\\������\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\������\\output.txt");
	ofstream oo("output.txt");
	int j; // �ܾ� �� ���縵 üũ
	int k;// ���� �� ���縵 üũ
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
		for (j = 0; j < word.length(); j++)  // �ܾ�üũ
		{
			for (k = 0; k < sentence.length(); k++) // ���� üũ
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