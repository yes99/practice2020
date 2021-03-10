#include <stdio.h>

int main()
{
    int a = 5;
    printf("a    %d\n",a);
    printf("&a   %d\n",&a);
    //printf("%p\n",&a);

    int* pa = &a;
    printf("pa   %d\n",pa);
    printf("&pa  %d\n",&pa);
    
    int** ppa = &pa;
    printf("ppa  %d\n",ppa);
    printf("&ppa %d\n",&ppa);

    printf("a = %d, *pa = %d, they must be the same \n", a, *pa);



}