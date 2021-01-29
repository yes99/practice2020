#include <iostream>

using namespace std;
int arr[1000] = { 10,23,1,1,23,23,4,5,6,7 };
int a[1000];
void counting_sort(int list[])
{
	int temp[1000];
	int count[1000];
	memset(temp, 0, sizeof(temp));
	//더해주기
	for (int i = 0; i < 10; i++)
		temp[list[i]]++;
	count[0] = temp[0];
	//누적으로 더해주기
	for (int i = 1; i <= 23; i++)
		count[i] = count[i - 1] + temp[i];
	//더해졌는지 확인
	for (int i = 0; i <= 23; i++)
		cout << count[i] << " ";
	cout << endl;
	//제일 끝에서 부터 삽입
	for (int i = 9; i >= 0; i--)
	{
		a[  count[ list[i] ]-1 ] = list[i];
		count[list[i]]--;
		//들어가는 위치 보기
		for (int j = 0; j < 10; j++)
			cout << a[j] << " ";
		cout << endl;
	}
	//정렬된 행렬
	for (int i = 0; i < 10; i++)
		cout << a[i] << " ";
	cout << endl;
}
int main()
{
	counting_sort(arr);
}