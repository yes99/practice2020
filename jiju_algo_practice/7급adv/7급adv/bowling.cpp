#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	string spad; //21개얌
	ifstream ii("D:\\input.txt");
	//ifstream ii("input.txt");

	ofstream oo("D:\\output.txt");
	//ofstream oo("output.txt");
	
	getline(ii, spad);
	int score =0;
	for (int i = 0; i < spad.length()-3; i++)
	{
		if (spad[i] > 47 && spad[i] < 58) // 숫자
		{
			score = score + spad[i] - 48;
		}
		else if (spad[i] == 45) // -
		{
			score = score + 0;
		}
		else if (spad[i] == 47) //  /
		{
			if (spad[i + 1] == 88)
			{
				score = score + 10 - (spad[i - 1] - 48) + 10;
			}
			else
			{
				score = score + 10 - (spad[i - 1] - 48) + spad[i + 1] - 48;
			}
		}
		else if (spad[i] == 88) // X
		{
			if (spad[i + 2] == 88)
			{
				score = score + 10 + 10 + spad[i + 4]-48;
			}
			else
			{
				if (spad[i + 3] == 47)
				{
					score = score + 10 + 10;
				}
				else
				{
					score = score + 10 + spad[i + 2] - 48 + spad[i + 3] - 48;
				}
			}
		}
		else if (spad[i] == 66 || spad[i] == 71) // B G
		{
			score = score + 0;
		}
	}
	int j;
	//for (j = spad.length() - 3; j < spad.length(); j++)
	//{
		//스트라이크 먼저 짜자
		if (spad[18] == 88)
		{
			score = score + 10;
			if (spad[19] == 88 && spad[20] == 88) // 두개다 스트라이크
			{
				score = score + 20;
			}
			else if (spad[20] == 47) // 끝에 스페어
			{
				score = score + 10;
			}
			else //둘다 숫자
			{
				score = spad[19] - 48 + spad[20] - 48;
			}
		}
		else if (spad[19] == 47)
		{


		}
	//}

	oo << score;
	ii.close();
	oo.close();
	return 0;
}