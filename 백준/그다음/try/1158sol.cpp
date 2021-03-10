#include <iostream>
#include <list>
using namespace std;

void Josephus(int n, int k);
int main()
{
    ios::sync_with_stdio(NULL);
    cin.tie(NULL);
    int N, K;
    cin >> N >> K;
    Josephus(N, K);
}
void Josephus(int n, int k)
{
    list<int> lis;
    for (int i = 1; i < n + 1; i++)
        lis.push_back(i);
    list<int>::iterator kill = lis.begin();  //주소값 시작점 불러오기
    cout << "First kill : " << *kill<<endl;
    for (int i = 0; i < k - 1; i++)
        kill++; //올바른 주소값 찾아가기
    cout << "NEXT Kill : " << * kill <<endl;

    cout << '<';

    //사람 죽이는거 열심히 카운트 합시다.

    while (n > 0) // 사람이 아무도 남지 않을대 까지 ㄱㄱ
    {
        if (n == 1) // 혼자 남았다면 그 숫자를 카운트 합시다.
        {
            cout << *kill;
            break;
        }
        cout << *kill << ", ";
        kill = lis.erase(kill);  // erase하면 한칸 앞으로감 그래서 k-1번만 더하는거임
        if (kill == lis.end())
            kill = lis.begin(); //원형큐라서 한번 복구해줘야함
        --n; // n 줄여야 함
        for (int i = 0; i < k - 1; i++) // 이거 다음 킬 카운트 까지 가는거
        {
            kill++; // 이건 죽인 사람을 카운트 한다.
            if (kill == lis.end()) // 죽인 사람 카운트 한게 리스트 만큼 되면
                kill = lis.begin();
        }
    }
    cout << '>';
}