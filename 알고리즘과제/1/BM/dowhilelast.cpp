#include <iostream>
#include <string>
using namespace std;

int main() {
  // 검색 대상 문자열
  string t = "ABCABCABCABCABC";

  // 어떤 문자들을 찾아볼 것인가?,2
  string p = "AB";
  int found= -1;
  int answer;
  do
  {
      found = t.find(p, found+1);
      cout<<"Found at: " << found <<endl;
      if(found !=-1)
      {
          answer = found;
      }

      /*if(found!=-1)
      {
          cout<<"Found at: " << found <<endl;
      }*/
  }while(found !=-1);
  cout<<"last time is " << answer;

}