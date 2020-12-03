#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <stdio.h>  // puts()
#include <string.h> // strlen()
#include <fcntl.h>  // O_WRONLY
#include <unistd.h> // write(), close()




#define BUFSIZ 200
int main(int argc, char *argv[])
{
    int fd1, fd2, n;
    char buf[BUFSIZ];
    char name[200];
    scanf("%s", name);

    if ((fd1 = open(name, O_RDONLY)) >0)
    {
        read(fd1, buf, BUFSIZ);
        char *ptr = strtok(buf, "\n"); 
        printf("FLAG_DOWNLOAD|2016112648|%s\n", ptr);
        while (ptr != NULL) // 자른 문자열이 나오지 않을 때까지 반복
        {
            // 자른 문자열 출력
            if(ptr = NULL)
            {
             printf("FLAG_DOWNLOAD|2016112648|[Download] Done");       
            }
            ptr = strtok(NULL, "\n"); // 다음 문자열을 잘라서 포인터를 반
            printf("FLAG_DOWNLOAD|2016112648|%s\n", ptr);
 
        }
        close(fd1);
    }
    else
    {
        printf("FLAG_DOWNLOAD|2016112648|[Err] not found file");
    }
    
}
