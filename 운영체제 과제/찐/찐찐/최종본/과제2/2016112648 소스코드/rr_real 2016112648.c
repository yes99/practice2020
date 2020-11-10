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
  scanf("%d",&n); 
  remain=n; 
  for(cnt=0; cnt<n; cnt++) 
  { 
    printf("Enter Arrival Time and Burst Time and Priority for Process Process Number %d :",cnt); 
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
      flag=1; 
      printf("Process[%d] has worked till %d\n",cnt, time);
    } 

    else if(remain_time[cnt]>0) 
    { 
      remain_time[cnt]-=Q; 
      time+=Q; 
      printf("Process[%d] has worked till %d\n",cnt, time);

    }
     
    if(remain_time[cnt]==0 && flag==1) 
    { 
      remain--; 
      printf("==========================\n");
      printf("P[%d] complete \t||\t%d\t||\t%d\n",cnt,time-arr_time[cnt],time-arr_time[cnt]-bur_time[cnt]); 
      printf("P[%d] complete time is %d\n",cnt, time);
      wait_time+=time-arr_time[cnt]-bur_time[cnt]; 
      turnaround_time+=time-arr_time[cnt]; 
      flag=0; 
    } 

    if(cnt==n-1) 
    {
      cnt=0; // 우리가 진행중인 큐 다 돌았을 경우 다시 0으로가야한다

    } 
    else if(arr_time[cnt+1]<=time)  //q 는 0부터 흐르지만 시간은 1부터 흐르므로
     {
       cnt++; //  새로운 프로세스가 들어와서 큐 자체를 늘려준다 
     } 
    else
    { 
      cnt=0;  // 그 외의 경우들 모두 1으로 간다
    }
    
  } 
  printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
  printf("Avg Turnaround Time = %f",turnaround_time*1.0/n); 
  
  return 0; 
}