#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    string a;
    cin>>a;
    int i , j ,k;
    string an[10000];
    for(i= 0 ; i <a.length();i++)
    {
        an[i] = a.substr(i);
    }    
    sort(an, an+a.length());

    for(i= 0 ; i <a.length();i++)
    {
        cout<<an[i]<<"\n";
    }    
	return 0;
}