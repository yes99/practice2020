# include <stdio.h>


int main()
{
    int caress;
    int opt;
    caress = rand() % (20+1-10) + 10;

    printf("여자분을 어디를 애무 하실 겁니까?\n");
    printf("1. 가슴 \n 2. 다리");
    scanf("%d", &opt);

    for(int i; i>100; i + caress )
    {
        if (opt == 1)
        {
            
        }    
    }

}


 
 
 /*randTemp = rand() % (b+1-a) + a;
따라서, 위의 코드를 쓰면 0+a ~ (b-1+a+1-a)
즉, a~b 중의 수를 뽑을 수 있다.
*/