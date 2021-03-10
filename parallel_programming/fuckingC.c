#include <stdio.h>


void ticktoc(char *arr)
{
    arr[0] += 1

    for (int i =0 ; i < strlen(arr)-1; i++)
    {
        if (arr[i] == 16)
            {
                arr[i] = 0;
                arr[i+1] += 1;
                if (i == len(arr)-1)
                {
                    arr[i+1] = 0;    
                }

}

