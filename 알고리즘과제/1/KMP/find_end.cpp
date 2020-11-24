#include <iostream>
#include <string>
using namespace std;

int main() {
  // 검색 대상 문자열
  string str = "ABCABCABCABCABC";

  // 어떤 문자들을 찾아볼 것인가?,2
  string search_str = "CAB";
  cout << "let's find "<< search_str<< endl;
  cout << str.find_first_of(search_str) << '\n';
  //cout << str.find_last_of(search_str, 1) << '\n';

  // 'x' 는 Hello World 에 없으므로 npos 가 리턴된다
  //cout << str.find_first_of('x') << '\n';
}