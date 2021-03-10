#include <iostream>
#include <string>

using namespace std;

int main()
{
    string all;
    getline(cin, all);
    cin.ignore();
    int n;
    cin>> n;
    int i, j ,k;
    string stree[100];
    int l[100];
    for(i = 0 ; i < n ; i++)
    {
        getline(cin,stree[i]);
        l[i] = stree[i].length()-1;
    }
    string nskill[100];
    int cnt = 0;

    for(i = 0; i < n ; i++)
    {
        for(j = i+1; j<n;j++)
        {
            if(stree[i][l[i]]==stree[j][0])
            {
                nskill[cnt] = stree[i] + stree[j].substr(1,l[j]);
                cnt++;
            }
        }
    }

    for(i = 0 ; i <cnt; i++)
    {
        cout << nskill[i] << endl;
    }
}