#include <iostream>
#include <string>
using namespace std;

int suffix(string pattern, int a)
{
    int i, j;
    int l = pattern.length();
    int suf = -1;
    int check;
    for (j = 0; j < a + 1; j++)
    {
        for (i = 0; i <l; i++)
        {
            check = l - j + i - 1;

            if (j > l / 2)
            {
                break;
            }
            else if (pattern[i] == pattern[check])
            {
                suf = i;
            }
            else
            {
                break;
            }
        }
    }
    return suf + 1;
}

int matchjump(string pattern, string part, int i, string originpattern)
{
    int found = -1;
    int answer;
    int save1 = -100;
    int save2 = -100;
    int m = originpattern.length();
    int q = suffix(originpattern, m-i-1);
    cout << "suffix is " << q << endl;
    do
    {
        found = pattern.find(part, found + 1);
        if (found != -1) //찾긴 찾음?
        {
            if (originpattern[found - 1] != originpattern[i-1])
            {
                save1 = found;
            }
            else
            {
                save2 = found;
            }
            cout <<"P(r-1) = " <<originpattern[found - 1] <<"  P(k) =" << originpattern[i] << endl;
            cout << "found at " << found << " ||save1 :" << save1 << " save2 :" << save2<< endl;
        }
    } while (found != -1);

    cout << "FINAL SAVE||" << "save 1 :" << save1 << " save 2 :" << save2<< endl;
    cout<< "m = " << m  << " k  = " <<i  << " q =  " << q << " r = " << save1+1 << endl;

    if (save1 == -100 && save2 == -100)  //1  일치하는 것이 없어서 
    {
        answer = m - i + m - q;
        cout << 1 <<endl;
    }
    else if (save1 == -100 && save2 != -100) //2
    {
        answer = m - i + m - q;
        cout << 2 <<endl;

    }
    else if(save1 != -100 && save2 == -100) //3
    {
        answer = m- (save1+1)+1;
        cout << 3 <<endl;

    }
    else if (save1 == 0 && save2 !=-100) //특별 예외사항
    {
        answer = m - i + m - q;
        cout << "exception" <<endl;
    }
    else //4
    {
        answer = m- (save1+1) +1;
        cout << 4 <<endl;

    }
    
    return answer;
}

void mjarray(string p, int mj[])
{
    int i,j,k;
    int m = p.length(); //6
    int matchjumpnum;
    string temppattern;
    string temppart;
    mj[m] = 1;
    for (i = m - 1; i > 0; i--) // 자 돌릴게요...
    {
        temppattern = p.substr(0, m-1);
        temppart = p.substr(i, m);

        cout << i << " position wrong p[" << i << "] " << temppattern << " " << temppart << endl;
        matchjumpnum = matchjump(temppattern, temppart, i , p);
        mj[i] = matchjumpnum;
        cout <<endl;
    }
}


void calbm(string t, string p, int mj[])
{
    int i , j;
    int cnt;
    int m = p.length(); //6
 
    for (i = 0; i < t.length(); i++)
    {
        cnt = 0;
        for(j=0;j<m;j++)
        {
            if(t[i+m-1-j] != p[m-j-1])
            {
                break;
            }
            else
            {
                cnt++;
            }
        } 
        if (cnt == p.length())
        {
            printf("\nfind at %d\n", i);
            i = i + mj[1] - (m-(1)) -1;
        }
        else
        {
            //핵심구간
            cout<< "now you are at " << i <<endl;

            i = i + mj[m-j] - (m-(m-j)) -1;
        }    
    }
}



int main()
{
    // 검색 대상 문자열
    string t = "abababababab";   //"abcbcabbabababcaabbcceabedabcabcabaggwehwehawhwhahraehjeaj";
    // 어떤 문자들을 찾아볼 것인가?,2
    string p = "abab" ;  //"edabcabcab";
    int i,j,k;
    int mj[100];
    int m = p.length(); //6
    int cnt;
    cout << endl;

    mjarray(p, mj);

    cout << endl;
    for(i=1;i < m+1;i++)
    {
        cout << mj[i]<< " ";
    }
    cout << endl;
    
    calbm(t, p, mj);


    //핵심구간

}