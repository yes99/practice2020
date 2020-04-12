#include <stdio.h>

int roundfunction(int i);


int main()
{
    int number;
    float MAX_NUM;
    int modnum;
    printf("size of SQUARE: ");
    scanf("%d", &number);

    modnum = roundfunction(number);
//반올림 해서 cycle 횟수 정하는거 완료

//int square[number][number];

    int square[10000][10000];
//주석 처럼 하고 싶은데 안돼서 그냥 질러 놓음    
    
    /*
    for (i=0; i<modnum; i++)
    {
        for(j=0; j<modnum; j++)
        {
            
        }
    }
    */

   int count =0;
   int current_number =0;
   int x=0, y=0;
   // 일단 변수 선언



}



int roundfunction(int i)
{
    int cycle;
    if(i%2==1) //홀수다
    {
    cycle = i /2 +1 ;
    }
    else
    {
    cycle = i /2 ;
    }

    return cycle;

}