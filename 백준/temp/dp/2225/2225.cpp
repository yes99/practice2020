#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    int n;
    int k;
    cin>>n;
    cin>>k;
    int i , j;
    int tempk = 1;
    int tempn = n+1;
    long long nn=1 , kk=1;
    //cout<< tempn << "/" <<tempk << " * ";
    for(i = 1; i <= k+1 ; i++)
    {
        cout<< tempn << "/" << tempk << "   ";
        nn = (nn * tempn)%1000000000;
        tempn--;
        kk = (kk * tempk)%1000000000;
        tempk++;
        cout << nn << "  " << kk <<endl;
    }
    //cout<<endl<< nn << " " << kk << endl;
    cout <<endl<< nn << "   " << kk <<endl;
    int answer = (nn/kk)%1000000000;
    //cout<< " =" <<answer%1000000000;
    //cout<< answer% 1000000000;
    //int ranswer =  answer;
    //int ranswer = ranswer % 1000000000;
    cout <<endl << answer;
}
