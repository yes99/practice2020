#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;
// ii >>
// oo <<
int main()
{
    string whole;
    char wholearr[500];
    int i, j, k;
    //ifstream ii("C:\\?��?��?��\\input.txt");
    ifstream ii("inputappendtab.txt");
    //inputappendtab input

    getline(ii, whole);
    cout << "string ::" << whole << endl;

    strcpy(wholearr, whole.c_str());
    cout << "char[] ::";
    for (i = 0; i < whole.length(); i++)
    {
        cout << wholearr[i];
    }
    cout << endl << endl;

    char *ptr = strtok(wholearr, "^"); // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
    cout << ptr << endl;  

    while (ptr != NULL) // 자른 문자열이 나오지 않을 때까지 반복
    {
        cout << ptr << endl;     // 자른 문자열 출력
        ptr = strtok(NULL, "^"); // 다음 문자열을 잘라서 포인터를 반환
    }


    ii.close();
    return 0;
}