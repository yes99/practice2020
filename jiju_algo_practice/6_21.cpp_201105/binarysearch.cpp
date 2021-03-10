#include <iostream>
using namespace std;


int main()
{
	int a[] = { 2,5,7,8,12,15,57,72,88,93,100 };
	int n = 11;
	int s;

	cout << "찾을 숫자는? ";
	cin >> s;

	int low = 0, high = n, m, flag = 0;
	while (low <= high)
	{
		m = (low + high) / 2;
		if (s == a[m])
		{
			flag = 1;
			break;
		}
		if (s > a[m])
		{
			low = m + 1;
		}
		else
		{
			high = m - 1;
		}
	}

	if (flag == 0)
	{
		cout << s << "는 없는 데아티입니다" << endl;
	}
	else
	{
		cout << s << " 는 " << m << "번째에 있습니다" << endl;
	}

	return 0;
}