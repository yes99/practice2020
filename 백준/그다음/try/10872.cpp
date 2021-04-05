#include <iostream>
#include <vector>
using namespace std;

int factorial(int num)
{
    if (num <= 1) return 1;
 
    return num * factorial(num - 1);
}
 
int main(void)
{

   //ios_base::sync_with_stdio(0);
    //cin.tie(0);
   
    int num;
    //cin >> num;
    scanf("%d", &num);
    int result = 0;
 
    //factorial recursive
    result = factorial(num);
 
    //print
    int cnt = 0;
    while(result % 10 ==0)
    {
        //cout <<result <<endl;

        if(result % 10 ==0)
        {
            cnt++;
            result = result /10;
        }

    }

//    cout << cnt;
    printf("%d", cnt);

    return 0;

}
