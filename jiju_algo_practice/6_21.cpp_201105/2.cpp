#include <iostream>
#include<fstream>
#include<string>
#include <math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int n;
	string sentence;

	//ifstream ii("C:\\������\\input.txt");
	ifstream ii("input.txt");
	
	//ofstream oo("C:\\������\\output.txt");
	ofstream oo("output.txt");
	ii >> n; ii.ignore();
	char alpha = 65;
	char array[26]; // ���ĺ� �ʱ�ȭ
	int answer[26];
	// ���� �ʱ�ȭ
	for (int i = 0; i < 26; i++)
	{
		answer[i] = 0;
	}
	//ABC�迭 �ʱ�ȭ -> �� ����
	/*for (int i = 0; i < 26; i++)
	{
		array[i] = alpha;
		oo << array[i] << " ";
		alpha = alpha + 1;
	}*/
	char check;
	//��ȣ���� �ҹ��� ���� �빮��ȭ
	for (int i = 0; i < n; i++)
	{
		getline(ii, sentence);
		for (int j = 0; j < sentence.length(); j++)
		{
			if (sentence[j] > 96 && sentence[j] < 123)
			{
				sentence[j] = sentence[j] - 32;
			}
			//��������
			if (sentence[j] > 64 && sentence[j] < 91)
			{
				check = (sentence[j] - 65) % 26;
				answer[check]++;
			}

			/*for (int k = 0; k < 26; k++)
			{
				//�Լ���, ���� ������ �׶��׶� üũ �ؼ� ���ϱ�
				if (array[k] == sentence[j])
				{
					answer[k]++;
				}
			}*/
			//oo << sentence[j];
		}
		//oo << endl;
	}

	//oo << endl;
	/*
	�ϴ�, �迭�� Ȯ���� ���� �Ǿ��ٴ� �� Ȯ����  
	for (int i = 0; i < 26; i++)
	{
		oo << answer[i] << " ";
	}
	*/
	int max = answer[0];
	int output = 0;
	//�迭�ȿ��� ���� ū �� ã��
	for (int i = 0; i < 26; i++)
	{
		if (answer[i] > max)
		{
			max = answer[i];
			output = i;
		}
		else if (answer[i] == max)
		{

		}
	}
	char final = output + 65;
	oo << final  << " " << max;

	ii.close();
	oo.close();
	return 0;
}