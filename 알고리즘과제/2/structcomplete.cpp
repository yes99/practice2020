#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;
// ii >>
// oo <<
struct music
{
    int rank;
    string name;
    string singer;
    string album;
    int like;
};

int main()
{
    music m[100];
    string whole;
    string temp;
    char wholearr[500];
    int i, j, k;
    int structcnt=0;
    int iptr;
    //ifstream ii("C:\\?��?��?��\\input.txt");
    ifstream ii("finalinput.txt");
    //inputappendtab input
    for (i = 0; i < 10; i++)
    {
        getline(ii, whole);
        strcpy(wholearr, whole.c_str());
        char *ptr = strtok(wholearr, "\t"); // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
        temp = ptr;
        iptr = stoi(temp);
        m[i].rank = iptr;
        cout << ptr << " start"  <<endl;
        while (ptr != NULL)                 // 자른 문자열이 나오지 않을 때까지 반복
        {
                               // 자른 문자열 출력
            ptr = strtok(NULL, "\t"); // 다음 문자열을 잘라서 포인터를 반환
            if(structcnt == 0)
            {
                temp = ptr;
                cout << ptr <<" 0 " << endl;
                m[i].name = temp;
            }
            else if(structcnt == 1)
            {
                temp = ptr;
                cout << ptr<<" 1 "  << endl;
                m[i].singer = temp;
            }
            else if(structcnt == 2)
            {
                temp = ptr;
                cout << ptr<<" 2 "  << endl;
                m[i].album = temp;
            }
            else if(structcnt == 3)
            {
                temp = ptr;
                iptr = stoi(temp);
                cout << ptr <<" 3 "  << endl;
                m[i].like = iptr;
            }
            structcnt++;
        }
        structcnt = 0;
    }
    ii.close();

    for( i =0 ; i < 10 ; i++)
    {
        cout << m[i].rank << " " <<m[i].name << " " <<m[i].singer << " " <<m[i].album << " " << m[i].like <<endl;
    }

    return 0;
}


//할일 :: array to string 바꿔주는거 중간에 포함해야함    스트럭트 정리 똑바로 하고  스트럭드테 다 들어가나 똑바로 확인