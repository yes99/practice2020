#include <stdio.h>
int main() {
  FILE *fp, *fp2;
    char imsg[100];
    scanf("%s", &imsg);
  if ((fp = fopen(imsg, "r")) == NULL) 
  {
    printf("error! \n");
    printf("%d", fp);
    return 0;
  }

  fputs("hello guys \n Psi 입니다 \n", fp);

  if ((fp2 = fopen(imsg, "a")) == NULL) {
    printf("error! \n");
    return 0;
  }

  fputs("hello man?", fp2);
  return 0;
}