#include <iostream>
#include <string>
using namespace std;

int lastword(string text, string pattern)
{
     int found= -1;
  int answer;
  do
  {
      found = text.find(pattern, found+1);
     // cout<<"Found at: " << found <<endl;
      if(found !=-1)
      {
          answer = found;
      }

      /*if(found!=-1)
      {
          cout<<"Found at: " << found <<endl;
      }*/
  }while(found !=-1);
  return answer;
}



int main() {
  // 검색 대상 문자열
  string t = "ABCABCABCABCABC";

  // 어떤 문자들을 찾아볼 것인가?,2
  string p = "CA";
  int ln;

  ln = lastword(t,p);
    cout<<"last time is " << ln;


}