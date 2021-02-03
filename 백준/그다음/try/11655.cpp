#include <iostream>
#include <string>
using namespace std;

int main()
{
    //대문자 65 89
    //소문지 97 122

    string word;
    getline(cin, word);
    int i, j, k;
    for (i = 0; i < word.length(); i++)
    {
        if (word[i] <= 90 && word[i] >= 65)
        {
            word[i] = ((word[i] - 65 + 13) % 26) +65 ;
        }
        else if (word[i] <= 122 && word[i] >= 97)
        {
            word[i] = ((word[i] - 97 + 13) % 26) + 97 ;
        }
    }

    cout << word;
}