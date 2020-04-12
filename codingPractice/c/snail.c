#include <stdio.h>

int main()
{
int number;
float MAX_NUM;
int cycle;
printf("size of SQUARE: ");
scanf("%d", &number);

if(number%2==1) //홀수다
{
    cycle = number /2 +1 ;
}
else
{
    cycle= number /2 ;
}

printf("\n\n\n%d", cycle);



/*
float number2 = number;

printf("\n\n%f", number2/2);
*/



}