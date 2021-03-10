#include <iostream>
using namespace std;

int main()
{
	int big[10], div[10], answer[10], sur[10];
	int lbig, ldiv, cnt, borrow;
	int i, j, k, w, t;
	string sbig("0458");
	string sdiv("010");

	lbig = sbig.length() - 1;
	ldiv = sdiv.length() - 1;
	k = 0;

	for (i = 0; i <= lbig; i++)
	{
		big[i] = sbig[i] - '0';
	}
	for (i = 0; i <= ldiv; i++)
	{
		div[i] = sdiv[i] - '0';
	}
	//---------------------divide start
	for (i = ldiv; i <= lbig; i++)
	{
		cnt = 0; // »¬¼ÀÀÇ È½¼ö
		do
		{
			for(j =0; j <=ldiv; j++)      //»¬»ù ÇÒ¼ö ¾ø´Â °æ¿ì ´ëºñ (¸¶Áö¸·)
			{
				sur[j] = big[i - ldiv + j];
			}
			//»¬¼ÀºÎºÐ
			borrow = 0;
			for (j = ldiv; j >= 0; j--)
			{
				w = i - ldiv + j;
				t = big[w] - div[j] - borrow;
				if (t < 0)
				{
					borrow = 1;
					big[w] = t + 10;
				}
				else
				{
					borrow = 0;
					big[w] = t;
				}
			}
			cnt++;
		} while (borrow != 1);
		for (j = 0; j <= ldiv; j++)
		{
			big[i - ldiv + j] = sur[j];
		}
		answer[k] = cnt - 1;
		k++;
	}
	cout << "¸ò     = ";
	for (i = 0; i < k; i++)
	{
		cout << answer[i];
	}
	cout << endl;
	cout << "³ª¸ÓÁö =  ";
	for (i = 0; i < ldiv; i++)
	{
		cout << sur[i];
	}
	cout << endl;


	return 0;
}