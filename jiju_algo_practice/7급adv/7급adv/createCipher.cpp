#include <iostream>
#include<fstream>
#include<string>
#include<math.h>
using namespace std;
// ii >>
// oo <<
int main()
{
	int num;
	string cipher;

	//ifstream ii("C:\\이현석\\input.txt");
	ifstream ii("input.txt");
	//ofstream oo("C:\\이현석\\output.txt");
	ofstream oo("output.txt");
	ii >> num;
	ii.ignore();
	int l;
	int i, j,k,m;
	for(i = 0 ; i < num ; i++)
	{
		getline(ii, cipher);
		l = cipher.length();
		for( j =0; j < l ; j++)
		{
			if(cipher[j] == '#')
			{
				cipher.erase(j-1, 1);
				cipher.erase(j-1, 1);
				j = 0;
				l = cipher.length();
			}
		}
		l = cipher.length();
		for( k = l ; k > 0 ; k--)
		{
			if(cipher[k] == '?')
			{
				cipher.erase(k, 1);
				cipher.erase(k, 1);
				l = cipher.length();
			}
		}
		for( m = 0 ; m < l ; m++)
		{
			if(cipher[m] == '&')
			{
				cipher = "";
				break;
			}
		}

		oo << cipher<<endl;
	}
	
	ii.close();
	oo.close();
	return 0;
}