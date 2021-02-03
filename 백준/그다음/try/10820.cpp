#include <iostream>
#include <string>
using namespace std;

int main()
{
    string word;
    int j;
    while (getline(cin, word))
    {
        int big = 0, small = 0, number = 0, space = 0;
        for (j = 0; j < word.size(); j++)
        {
            if (word[j] >= 'A' && word[j] <= 'Z')
            {
                big++;
            }
            else if (word[j] >= 'a' && word[j] <= 'z')
            {
                small++;
            }
            else if (word[j] >= '0' && word[j] <= '9')
            {
                number++;
            }
            else if (word[j] == ' ')
            {
                space++;
            }
        }
        cout << small << " " << big << " " << number << " " << space << "\n";
    }
    return 0;
}