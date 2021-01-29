#include <iostream>
using namespace std;

int main()
{
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);

    int n, a, b, swap;

    long long array[1005];
    int i;

    cin >> n;

    for (i = 0; i < n; i++)
        cin >> array[i];

    for (a = 0; a < n - 1; a++)
    {
        for (b = 0; b < n - a - 1; b++)
        {
            if (array[b] > array[b + 1])
            {
                swap = array[b];
                array[b] = array[b + 1];
                array[b + 1] = swap;
            }
        }
    }

    int j;
    for (i = 0; i < n; i++)
    {
        if (array[i] == array[i + 1])
        {
            for (j = i + 1; j < n; j++)
            {
                array[j] = array[j +1];
            }
            n--;
            //cout<<"minus"<<endl;
            i--;
        }
    }
    for (i = 0; i < n; i++)
    {
        cout << array[i] << endl;
    }
}


/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int num,tmp;
    vector<int> a;
    cin >> num;
    for(int i = 0; i < num; i++)
    {
        cin >> tmp;
        a.push_back(tmp);
    }
    sort(a.begin(),a.end());
    for(int i = 0; i < num; i++)
        cout << a[i] << '\n';
}
*/