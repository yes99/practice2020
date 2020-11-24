#include <iostream>
#include <string>
using namespace std;
int main()
{
    string str("aa bb aa bb aa bb");
    cout << "±æÀÌ:" << str.length() << endl; //17
    cout << str.find("aa") << endl; //0
    cout << str.find("bb") << endl; //3
    cout << str.rfind("bb") << endl; //15
    cout << str.find_first_of("aa") << endl; //0
    cout << str.find_first_not_of("aa") << endl; //2
    cout << str.find_first_of("bb") << endl;; //3
    cout << str.find_last_of("aa") << endl; //13
    return 0;
}