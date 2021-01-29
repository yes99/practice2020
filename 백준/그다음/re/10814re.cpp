#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

struct member
{
    int age;
    string name;
};
member info[100001];

bool comp( member a,  member b)
{
    return a.age < b.age;   
}

int main()
{

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> info[i].age >> info[i].name;
    }

    stable_sort(info, info + n, comp);

    for (int i = 0; i < n; i++)
    {
        cout << info[i].age << " "<< info[i].name<<"\n";
    }
}
