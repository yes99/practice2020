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
	//ifstream ii("C:\\������\\input.txt");
	ifstream ii("input.txt");

	//ofstream oo("C:\\������\\output.txt");
	ofstream oo("output.txt");
	string reverse[100]; // �ʴ� ����� �����
	char Ratom[100]; // �ʴ� �����¿�
	ii >> origin;
//	oo << "=================== ó�� ������" << endl;

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
	}*/ // reverse�� �������� ����� �����ϴ� �ֵ��̴�. 
//	oo << "=================== ���� �ֵ� ������" << endl;
	//---------------------------- ���� �ִ� �ֵ� ����
	string inputarray[100]; // �ִ� �ֵ��� �������� ������ ��
	char inputreverse[100]; // �ִ� �ֵ��� ������ ��
	string IRA[100]; //�ִ� �ֵ��� ����� ������ ��
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
//input �� ����� �ѹ� Ȯ���ߴ�. 
//��Ʈ�� �迭�ȿ� ������ �Ǵ°� Ȯ�� 	
	for (int i = 0; i < input; i++) // i �� �츮�� ������ ����
	{
		for ( j = 0; j < origin; j++) // j�� ���� �ִ� �ֵ�
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
	} // �Ųٷ� �־ ���  ������
//	oo << "======================= ���� �迭 �غ�" << endl;
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
	//oo << "=======================������ ���� �ٽ� ������" << endl;
	for (int i = 0; i < origin; i++)
	{
		oo << answer[i] << endl;
	}

	ii.close();
	oo.close();
	return 0;
}