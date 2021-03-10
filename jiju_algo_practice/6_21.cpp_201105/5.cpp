#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int origin;
	string oword;
	int input;
	string iword;
	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	string reverse[100]; // 너는 뒤집어서 저장용
	char Ratom[100]; // 너는 뒤집는용
	ii >> origin;
//	oo << "=================== 처음 뒤집음" << endl;

	for (int i = 0; i < origin; i++)
	{
		ii >> oword;
		//answer[i] = oword;
		for (int j = 0; j < oword.length(); j++)
		{
			Ratom[oword.length()-1 - j] = oword[j];
		}
		for (int j = 0; j < oword.length(); j++)
		{
			reverse[i] = reverse[i] + Ratom[j];
		}//check[i] = oword[oword.length()-1];
	}
/*	for (int i = 0; i < origin; i++)
	{
		oo << reverse[i] << endl;
	}*/ // reverse는 뒤집어진 행렬이 존재하는 애들이다. 
//	oo << "=================== 넣을 애들 뒤집음" << endl;
	//---------------------------- 이제 넣는 애들 조작
	string inputarray[100]; // 넣는 애들의 오리진을 저장할 곳
	char inputreverse[100]; // 넣는 애들을 뒤집을 곳
	string IRA[100]; //넣는 애들을 뒤집어서 저장할 곳
	ii >> input;
	for (int i = 0; i < input; i++)
	{
		ii >> iword;
		inputarray[i] = iword;
		for (int j = 0; j < iword.length(); j++)
		{
			inputreverse[iword.length() - 1 - j] = iword[j];
		}
		for (int j = 0; j < iword.length(); j++)
		{
			IRA[i] = IRA[i] + inputreverse[j];
		}//check[i] = oword[oword.length()-1];
	}

/*	for (int i = 0; i < input; i++)
	{
		oo << IRA[i] << endl;
	}*/
	string t;
	int j;
//input 도 뒤집어서 한번 확인했다. 
//스트링 배열안에 저장이 되는가 확인 	
	for (int i = 0; i < input; i++) // i 는 우리가 삽입할 갯수
	{
		for ( j = 0; j < origin; j++) // j는 원래 있는 애들
		{
			if (IRA[i] < reverse[j])
			{
				t = IRA[i];
				IRA[i] = reverse[j];
				reverse[j] = t;
			}
		}
		reverse[j] = IRA[i];
		origin++;
	} // 거꾸로 넣어서 모두  나열함
//	oo << "======================= 역순 배열 해봄" << endl;
/*	for (int i = 0; i < origin; i++)
	{
		oo << reverse[i] << endl;
	}*/
	string answer[100];
	char rFa[100]; // reverse for answer;

	for (int i = 0; i < origin; i++)
	{
		for (int j = 0; j < reverse[i].length(); j++)
		{
			rFa[reverse[i].length() - 1 - j] = reverse[i][j];
		}
		for (int j = 0; j <reverse[i].length(); j++)
		{
			answer[i] = answer[i] + rFa[j];
		}//check[i] = oword[oword.length()-1];
	}
	//oo << "=======================제출을 위해 다시 뒤집음" << endl;
	for (int i = 0; i < origin; i++)
	{
		oo << answer[i] << endl;
	}

	ii.close();
	oo.close();
	return 0;
}