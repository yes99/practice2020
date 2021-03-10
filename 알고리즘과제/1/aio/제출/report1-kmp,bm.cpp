#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <time.h>
using namespace std;
// ii >>
// oo <<
void txttostring(string code[],int n, string name[])
{
    int i, j, k;
    string temp;
    string text;
    string num;
    for (i = 0; i < n; i++)
    {
        text = "input";
        num = to_string(i);
        text.append(num);
        text.append(".txt");
        cout << text << endl;
        ifstream ii(text);
        while(getline(ii, temp))
        {
            code[i] = code[i] + temp;
        }
        name[i] = text;
        cout << "text[" << i << "] :" << code[i] << endl;
        ii.close();
    }

}
void inputtext(string code[], int n,string name[])
{
    int i, j, k;
    string temp;
    string text;
    cout << "how many programs : ";
    cin >> n;

    for (i = 0; i < n; i++)
    {
        cout << "input the name of the text file, make sure include .txt : ";
        cin >> text;
        ifstream ii(text);
        while (getline(ii, temp))
        {
            code[i] = code[i] + temp;
        }
        name[i] = text;
        cout << code[i]<<endl;;
        ii.close();
    }
}


void flowchart(string pattern, int fail[])
{
    int i;
    char Parray[100];
    int check, x;
    fail[1] = 0;
    fail[2] = 1;

    for (i = 1; i < pattern.length() + 1; i++)
    {
        Parray[i] = pattern[i - 1];
    }
    for (i = 1; i < pattern.length() + 1; i++)
    {
        //cout << Parray[i];
    }
    //cout << endl;
    //flow chart 작성 시작
    for (i = 3; i < pattern.length() + 1; i++)
    {
        if (Parray[i - 1] == Parray[fail[i - 1]])
        {
            fail[i] = fail[i - 1] + 1;
        }
        else
        {
            check = i;
            if (fail[fail[i - 1]] == 0)
            {
                fail[i] = 1;
            }
            else
            {
                x = fail[check - 1];
                do
                {
                    if (fail[x] == 0)
                    {
                        fail[check] = 1;
                        break;
                    }
                    else if (Parray[fail[x]] == Parray[i - 1])
                    {
                        fail[check] = Parray[i - 1] + 1;
                        break;
                    }
                    else
                    {
                        x = fail[x];
                    }
                } while (1);
            }
        }
    }
}

int kmpmove(string text, string pattern, int fail[])
{
    int move;
    int i, j;
    int cnt;
    int flag = 0;
    for (i = 0; i < text.length()-pattern.length()+1; i++)
    {
        //cout << "now you are at "<< i << "   ";
        cnt = 1;
        for (j = 0; j < pattern.length(); j++)
        {
            if (text[i + j] == pattern[j])
            {
                cnt++;
            }
            else
            {
                //cout << "miss match at " << i+j << endl;
                break;
            }
        }
        if (cnt == pattern.length() + 1)
        {
            //printf("\nfind at %d\n", i);
            move = cnt - fail[cnt-1];
            i = i + move - 2;
            flag = 1;
        }
        else
        {
            //핵심구간
            move = cnt - fail[cnt];
            i = i + move - 1;
        }
    }
    if (flag == 1)
    {
        return flag;
    }
    else
    {
        return flag;
    }
}

int suffix(string pattern, int a)
{
    int i, j;
    int l = pattern.length();
    int suf = -1;
    int check;
    for (j = 0; j < a + 1; j++)
    {
        for (i = 0; i < l; i++)
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
    int q = suffix(originpattern, m - i - 1);
    //cout << "suffix is " << q << endl;
    do
    {
        found = pattern.find(part, found + 1);
        if (found != -1) //찾긴 찾음?
        {
            if (originpattern[found - 1] != originpattern[i - 1])
            {
                save1 = found;
            }
            else
            {
                save2 = found;
            }
            //cout <<"P(r-1) = " <<originpattern[found - 1] <<"  P(k) =" << originpattern[i] << endl;
            //cout << "found at " << found << " ||save1 :" << save1 << " save2 :" << save2<< endl;
        }
    } while (found != -1);

    //cout << "FINAL SAVE||" << "save 1 :" << save1 << " save 2 :" << save2<< endl;
    //cout<< "m = " << m  << " k  = " <<i  << " q =  " << q << " r = " << save1+1 << endl;

    if (save1 == -100 && save2 == -100) //1  일치하는 것이 없어서
    {
        answer = m - i + m - q;
        //cout << 1 <<endl;
    }
    else if (save1 == -100 && save2 != -100) //2
    {
        answer = m - i + m - q;
        //cout << 2 <<endl;
    }
    else if (save1 != -100 && save2 == -100) //3
    {
        answer = m - (save1 + 1) + 1;
        //cout << 3 <<endl;
    }
    else if (save1 == 0 && save2 != -100) //특별 예외사항
    {
        answer = m - i + m - q;
        //cout << "exception" <<endl;
    }
    else //4
    {
        answer = m - (save1 + 1) + 1;
        //cout << 4 <<endl;
    }

    return answer;
}

void mjarray(string p, int mj[])
{
    int i, j, k;
    int m = p.length(); //6
    int matchjumpnum;
    string temppattern;
    string temppart;
    mj[m] = 1;
    for (i = m - 1; i > 0; i--) // 자 돌릴게요...
    {
        temppattern = p.substr(0, m - 1);
        temppart = p.substr(i, m);

        //cout << i << " position wrong p[" << i << "] " << temppattern << " " << temppart << endl;
        matchjumpnum = matchjump(temppattern, temppart, i, p);
        mj[i] = matchjumpnum;
    }
}

int calbm(string t, string p, int mj[])
{
    int i, j;
    int cnt;
    int flag = 0;
    int m = p.length(); //6

    for (i = 0; i < t.length()-p.length(); i++)
    {
        cnt = 0;
        for (j = 0; j < m; j++)
        {
            if (t[i + m - 1 - j] != p[m - j - 1])
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
            //printf("\nfind at %d\n", i);
            i = i + mj[1] - (m-(1)) -1;
            flag = 1;
        }
        else
        {
            //핵심구간
            i = i + mj[m - j] - (m - (m - j)) - 1;
        }
    }

    if (flag == 1)
    {
        return flag;
    }
    else
    {
        return flag;
    }
}

int main()
{

    string text[100];
    string badcode;
    int lcode;
    string codep[100];
    string textname[100];
    int i, j, k;
    int fail[100];
    int mj[100];
    int textoption;
    int howmanytext;
    cout<< "how many textfile";
    cin>> howmanytext;
    while (1)
    {
        cout << "how to get bad code"<<endl << "1. text already exist"<<endl <<"2.input directly"<<endl;
        cin>>textoption;
        if (textoption == 1)
        {
            txttostring(text, howmanytext, textname);
            break;
        }
        else if(textoption == 2)
        {
            inputtext(text, howmanytext,textname);
            break;
        }
        else
        {
            cout << "again ";
        }
    }
    /*cout << "for debug check" << endl;
    for (i = 0; i < howmanytext; i++)
    {
        cout << text[i] << endl;
    }*/
    cout<< "input your bad code";
    cin >> badcode;
    cout<< "length of bad code";
    cin >> lcode;
    int lbadcode = badcode.length();

    for (i = 0; i < lbadcode - lcode + 1; i++)
    {
        codep[i] = badcode.substr(i, lcode);
    }

    for (i = 0; i < lbadcode - lcode + 1; i++)
    {
        cout << i << " " << codep[i] << endl;
    }

    cout << "BM" << endl;
    clock_t start, end;
    int bmcnt = 0, kmpcnt = 0;
    int fbmcnt =0, fkmpcnt = 0;
    double bmt, kmpt;
    start = clock();
    for (j = 0; j <howmanytext; j++)
    {
        for (i = 0; i < lbadcode - lcode + 1; i++)
        {
            mjarray(codep[i], mj);
            if (calbm(text[j], codep[i], mj) == 1)
            {
                cout << "virus found at " << textname[j]<<endl;
                bmcnt++;
            }
        }
        if(bmcnt > 0)
        {
            fbmcnt++;
            bmcnt = 0;
        }
        else
        {
            cout<< textname[j] <<"th text do not have virus"<<endl;
        }
    }
    end = clock();
    bmt =double(end -start);

    cout << "BM" << endl;
    cout << "how many virus program :" << fbmcnt << endl;
    cout << "no virus " << howmanytext - fbmcnt<<endl;
    cout << "bmtime : "<< bmt<<"ms"<<endl;

    cout << " KMP" << endl;
    start = clock();

    for (j = 0; j <howmanytext; j++)
    {
        for (i = 0; i < lbadcode - lcode + 1; i++)
        {
            flowchart(codep[i], fail);

            if (kmpmove(text[j], codep[i], fail) == 1)
            {
                cout << "virus found at " << textname[j]<<endl;
                kmpcnt++;
            }
        }
        if(kmpcnt > 0)
        {
            fkmpcnt++;
            kmpcnt = 0;
        }
        else
        {
            cout<< textname[j] <<" text do not have virus"<<endl;
        }
    }
    end = clock();
    kmpt = double(end -start);
    cout << "KMP" << endl;
    cout << "how many virus program :" << fkmpcnt << endl;
    cout << "no virus " << howmanytext - fkmpcnt<<endl;
    
    
    cout << "kmptime : " <<kmpt<<"ms"<<endl;

    return 0;
}
