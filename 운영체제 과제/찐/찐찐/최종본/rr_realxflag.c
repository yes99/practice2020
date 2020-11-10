#include<stdio.h> 
 
int main() 
{ 
 
  int cnt,j,n;
  int time,remain,Q; // Q = time quantum
  int wait_time=0;
  int turnaround_time=0;
  int arr_time[10];			
  int bur_time[10];			
  int remain_time[10];	
  int pri[10]; 
  printf("Enter Total Process:\t "); 
  scanf("%d",&n); 
  remain=n; 
  for(cnt=0; cnt<n; cnt++) 
  { 
    printf("Enter Arrival Time and Burst Time and Priority for Process Process Number %d :",cnt+1); 
    scanf("%d",&arr_time[cnt]); 
    scanf("%d",&bur_time[cnt]);
    scanf("%d", &pri[cnt]);
    remain_time[cnt] = bur_time[cnt]; 
  } 
  printf("Enter Time Quantum:\t"); 
  scanf("%d",&Q); 
  printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n"); 
  for(time=0, cnt=0;remain!=0;) 
  { 
    if(remain_time[cnt]<=Q && remain_time[cnt]>0) 
    { 
      time+=remain_time[cnt]; 
      remain_time[cnt]=0; 
      printf("Process[%d] has worked at %d     [%d]finish    flag was 1\n",cnt, time, remain_time[cnt]);
    } 
    else if(remain_time[cnt]>0) 
    { 
      remain_time[cnt]-=Q; 
      time+=Q; 
      printf("Process[%d] has worked at %d     [%d]left     flag was 0\n",cnt, time, remain_time[cnt]);

    }
     
    if(remain_time[cnt]==0) 
    { 
      remain--; 
      printf("==========================\n");
      printf("P[%d]\t||\t%d\t||\t%d\n",cnt,time-arr_time[cnt],time-arr_time[cnt]-bur_time[cnt]); 
      wait_time+=time-arr_time[cnt]-bur_time[cnt]; 
      turnaround_time+=time-arr_time[cnt]; 
    } 

    if(cnt==n-1) 
    {
      cnt=0;
    } 
    else if(arr_time[cnt+1]<=time) 
     {
       cnt++;
     } 
    else
    { 
      cnt=0; 
    }
  } 
  printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
  printf("Avg Turnaround Time = %f",turnaround_time*1.0/n); 
  
  return 0; 
}