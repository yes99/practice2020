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



/*
float number2 = number;

printf("\n\n%f", number2/2);
*/



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