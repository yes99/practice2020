#include <stdio.h>
#include <stdlib.h>

#define LOOPTIME 8

void sum(int a[], int b){
    for (int i=0;i<b;i++){
        a[i]++;
    }
}

int main()
{
    int a[5] = {1,2,3,4,5};
    int b=5;

    sum(a,b);

    printf("%d %d %d %d %d", a[0],a[1],a[2],a[3],a[4]);
    
    return 0;
}