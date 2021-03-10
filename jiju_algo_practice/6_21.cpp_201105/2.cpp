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

	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");
	
	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> n; ii.ignore();
	char alpha = 65;
	char array[26]; // 알파벳 초기화
	int answer[26];
	// 정답 초기화
	for (int i = 0; i < 26; i++)
	{
		answer[i] = 0;
	}
	//ABC배열 초기화 -> 빈도 계산시
	/*for (int i = 0; i < 26; i++)
	{
		array[i] = alpha;
		oo << array[i] << " ";
		alpha = alpha + 1;
	}*/
	char check;
	//암호에서 소문자 전부 대문자화
	for (int i = 0; i < n; i++)
	{
		getline(ii, sentence);
		for (int j = 0; j < sentence.length(); j++)
		{
			if (sentence[j] > 96 && sentence[j] < 123)
			{
				sentence[j] = sentence[j] - 32;
			}
			//진법으로
			if (sentence[j] > 64 && sentence[j] < 91)
			{
				check = (sentence[j] - 65) % 26;
				answer[check]++;
			}

			/*for (int k = 0; k < 26; k++)
			{
				//함수로, 뭐랑 같은지 그때그때 체크 해서 더하기
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
	일단, 배열이 확실히 정렬 되었다는 것 확인함  
	for (int i = 0; i < 26; i++)
	{
		oo << answer[i] << " ";
	}
	*/
	int max = answer[0];
	int output = 0;
	//배열안에서 가장 큰 수 찾기
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