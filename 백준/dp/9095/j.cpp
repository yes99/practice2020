#include<stdio.h>
int dp[12] = { 0, };
int main()
{
   int T, n;
   scanf("%d", &T);

   dp[1] = 1; dp[2] = 2; dp[3] = 4;

   for (int i = 4; i <= 11; i++)
      dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
   for (int i = 0; i < T; i++)
   {
      scanf("%d", &n);
      printf("%d\n", dp[n]);
   }
}