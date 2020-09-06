#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii>>
// oo<<

int spare(char board, char plus, char exnum, int num);
int strike(char board, char plus, char twoplus, int num);
int normal(char board, int num);
int non(char board, int num);
char definer(char d);

int main()
{
	string spad;

	//ifstream ii("D:\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("D:\\output.txt");
	ofstream oo("output.txt");
	getline(ii, spad);
	int score = 0;
	for (int i = 0; i < spad.length() - 1; i++)
	{
		if (spad[i] > 47 && spad[i] < 58)  // 숫자
		{
			score = normal(spad[i], score);
			//oo<< i<< "번째    "<< score<<endl;
		}
		else if (spad[i] == 45 || spad[i] == 71 || spad[i] == 66) // 미스
		{
			score = non(spad[i], score);
			//oo<< i<< "번째    "<< score<<endl;			
		}
		else if (spad[i] == 47) // 스페어
		{
			score = spare(spad[i], spad[i+1], spad[i-1], score);
			//oo<< i<< "번째    "<< score<<endl;			
		}
		else if(spad[18]=='X') //&&spad[19]=='X'&&spad[20]=='X'
		{
			score = strike(spad[i], spad[i+1], spad[i+2], score);
			break;
		}
		else //스트라이크
		{	
			if (spad[i + 2] == 'X')
			{
				score = strike(spad[i], spad[i + 2], spad[i+4], score);
				//oo<< i<< "번째    "<< score<<endl;				
			}
			else
			{
				score = strike(spad[i], spad[i + 2], spad[i + 3], score);
				//oo<< i<< "번째    "<< score<<endl;
			}
		}
	}
	oo << score;
	ii.close();
	oo.close();
	return 0;
}

char definer(char d)
{
	if (d == '-' || d == 'G' || d == 'B') // 미스
	{
		d = '0';
	}
	return d;
}

int spare(char board, char plus, char exnum, int num) // 스페어
{
	definer(plus);
	definer(exnum);
	
	if (plus == 'X') // 추가점수가 스트라이크일때
	{
		num = num - (exnum -48) + 10 + 10;
		
	}
	else
	{
		num = num - (exnum- 48) + 10 + (plus-48);
	}
	return num;
}

int strike(char board, char plus, char twoplus, int num) //스트라이크
{
	definer(plus);
	definer(twoplus);

	if (plus > 47 && plus < 58 &&twoplus == '/') // 추가점수가 스페어
	{
		plus = 48;
		twoplus = 58;
	}
	else if (plus == 'X' && twoplus > 47 && twoplus < 58) // 추가점수가 스트라이크 한번
	{
		plus = 58;
	}

	else if (plus == 'X' && twoplus == 'X') // 추가점수가 모두 스트라이크
	{
		plus = 58;
		twoplus = 58;
	}
	num = num + 10 + (plus - 48) + (twoplus - 48);
	return num;
}

int normal(char board, int num)
{
	num = num + board - 48;
	return num;
}
int non(char board, int num)
{
	num = num + 0;
	return num;
}