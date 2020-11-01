#include <stdio.h>
#include <time.h>

int main () {
   time_t TIME;
   struct tm *sttime;
   char output[1000];

   time(&TIME);

   sttime = localtime(&TIME);

   strftime(output,1000,"%Y/%m/%d(%a)%X", sttime);
   printf("%s", output );
  
   return(0);
}
//2020/10/15(thur)20:15:30
//%G/%m/%d(%a)%T