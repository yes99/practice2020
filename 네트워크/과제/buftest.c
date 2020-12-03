#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char a[50] = "wewejkgjwiohgjwea;ohgjweihg";
    printf("%s\n", a);

    a[0] = '\0';
    printf("erased buffer?\n%s\n", a);


}