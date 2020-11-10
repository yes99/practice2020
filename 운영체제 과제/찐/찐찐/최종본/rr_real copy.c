#include<stdio.h> 
 
int main() 
{ 
  int cnt,j,n;
  int time,remain,flag=0,Q; // Q = time quantum
  int wait_time=0;
  int turnaround_time=0;
  int arr_time[10];							// Arrival Time
  int bur_time[10];							// Burst Time
  int remain_time[10];							// remaining Time
  int pri[10]; 
  printf("Enter Total Process:\t "); 
  scanf("%d",&n);    n = 5;
  remain=n; 
  arr_time[0]= 0;arr_time[1]=2; arr_time[2] = 3; arr_time[3] = 5 ;arr_time[4] = 9 ;
  bur_time[0] = 8;bur_time[1] = 4;bur_time[2] = 2;bur_time[3] = 1;bur_time[4] = 8;
  pri[0] =  0;pri[1] = 2;pri[2] = 1;pri[3] = 3;pri[4] = 0;
  for(cnt = 0 ;cnt < 5; cnt ++)
    remain_time[cnt] = bur_time[cnt]; 
  printf("Enter Time Quantum:\t"); 
  Q = 1;
  printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n"); 
  for(time=0, cnt=0;remain!=0;) 
  { 
    if(remain_time[cnt]<=Q && remain_time[cnt]>0) 
    { 
      time+=remain_time[cnt]; 
      remain_time[cnt]=0; 
      flag=1; 
      printf("Process[%d] has worked at %d     [%d]      flag is %d\n",cnt, time, remain_time[cnt], flag);
    } 

    else if(remain_time[cnt]>0) 
    { 
      remain_time[cnt]-=Q; 
      time+=Q; 
      printf("Process[%d] has worked at %d     [%d]      flag is %d\n",cnt, time, remain_time[cnt], flag);

    }
     
    if(remain_time[cnt]==0 && flag==1) 
    { 
      remain--; 
      printf("==========================\n");
      printf("P[%d] finished \t||\t%d\t||\t%d\n",cnt,time-arr_time[cnt],time-arr_time[cnt]-bur_time[cnt]); 
      wait_time+=time-arr_time[cnt]-bur_time[cnt]; 
      turnaround_time+=time-arr_time[cnt]; 
      flag=0; 
    } 

    if(cnt==n-1) 
    {
      cnt=0;
      printf("cnt is 0 because 1\n");

    } 
    else if(arr_time[cnt+1]<=time) 
     {
       cnt++;
       printf("cnt is %d because 2\n ", cnt); // cnt 는 큐 정해주는 거임 사실 cnt가 몇이냐에 따라 
     } 
    else
    { 
      cnt=0; 
      printf("cnt is 0 because 3\n");
    }
    
  } 
  printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
  printf("Avg Turnaround Time = %f",turnaround_time*1.0/n); 
  
  return 0; 
}