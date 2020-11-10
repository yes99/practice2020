#include<stdio.h> 
 
int main() 
{ 
 
  int count,j,n;
  int time,remain,flag=0,time_quantum; 
  int wait_time=0;
  int turnaround_time=0;
  int arr_time[10];							// Arrival Time
  int bur_time[10];							// Burst Time
  int remain_time[10];							// remaining Time
   
  printf("Enter Total Process:\t "); 
  scanf("%d",&n); 
  remain=n; 
  for(count=0; count<n; count++) 
  { 
    printf("Enter Arrival Time and Burst Time for Process Process Number %d :",count+1); 
    scanf("%d",&arr_time[count]); 
    scanf("%d",&bur_time[count]); 
    remain_time[count] = bur_time[count]; 
  } 
  printf("Enter Time Quantum:\t"); 
  scanf("%d",&time_quantum); 
  printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n"); 
  for(time=0, count=0;remain!=0;) 
  { 
    if(remain_time[count]<=time_quantum && remain_time[count]>0) 
    { 
      time+=remain_time[count]; 
      remain_time[count]=0; 
      flag=1; 
      printf("Process[%d] has worked arr_time %d\n",count, time);
    } 
    else if(remain_time[count]>0) 
    { 
      remain_time[count]-=time_quantum; 
      time+=time_quantum; 
      printf("Process[%d] has worked arr_time %d\n",count, time);

    } 
    if(remain_time[count]==0 && flag==1) 
    { 
      remain--; 
      printf("==========================\n");
      printf("P[%d]\t|\t%d\t|\t%d\n",count+1,time-arr_time[count],time-arr_time[count]-bur_time[count]); 
      wait_time+=time-arr_time[count]-bur_time[count]; 
      turnaround_time+=time-arr_time[count]; 
      flag=0; 
    } 
    if(count==n-1) 
      count=0; 
    else if(arr_time[count+1]<=time) 
      count++; 
    else 
      count=0; 
  } 
  printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
  printf("Avg Turnaround Time = %f",turnaround_time*1.0/n); 
  
  return 0; 
}