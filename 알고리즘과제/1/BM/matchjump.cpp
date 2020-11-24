#include <iostream>
#include <string.h>

#include <algorithm>
using namespace std;





int main()
{
    string p = "WOWWOW";
    string origin = p;
    int m ,r;
    int i, j;
    int mj[100];
    char check[100];
    int flag = 0;
    m =p.length(); //6 
    //입력
    for(i=1; i < m+1 ; i++)
    {
        check[i] = p[i-1];
    }
    /*for(i=1; i < m+1 ; i++)
    {
        cout<<check[i];
    }*/
    

    int checkr;
    string tempp;
    mj[m] = 1;
    for(i=m-1;i>0;i--) // 자 돌릴게요...
    {

        tempp = p.substr(0, i);
        cout << i << " position wrong p["<< i << "] " <<tempp << " "<<p.substr(i,m)<<" ";
        r = tempp.find_last_of(p.substr(i,m));
        cout <<r << endl;
        
    }
    

}