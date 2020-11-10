#include<stdio.h>
#include<conio.h>
int main()
{
int i,j,Number_of_Process,tot=0,flag,temp;
printf("Enter Number of Process:");
scanf("%d",&Number_of_Process);
int at[Number_of_Process],priority[Number_of_Process],bt[Number_of_Process],Process_no[Number_of_Process],wt[Number_of_Process],tat[Number_of_Process];
printf("\nEnter Arrival Time, Burst Time and priority\n");
for(i=0;i<Number_of_Process;i++)
{
    printf("\nP[%d]\n",(i+1));
    printf("Enter Arrival Time:");
    scanf("%d",&at[i]);
    printf("Enter Burst Time:");
    scanf("%d",&bt[i]);
    printf("Enter priority:");
    scanf("%d",&priority[i]);
    Process_no[i]=i+1;
}
for(i=0;i<Number_of_Process;i++)
{
    flag=i;
    for(j=i+1;j<Number_of_Process;j++)
    {
        if(priority[j]<priority[flag])
        flag=j;
    }
    temp=priority[i];
    priority[i]=priority[flag];
    priority[flag]=temp;
    temp=bt[i];
    bt[i]=bt[flag];
    bt[flag]=temp;
    temp=Process_no[i];
    Process_no[i]=Process_no[flag];
    Process_no[flag]=temp;
    temp=at[i];
    at[i]=at[flag];
    at[flag]=temp;
}
wt[0]=0;
for(i=1;i<Number_of_Process;i++)
{
    wt[i]=0;
    for(j=0;j<i;j++)
    {
    wt[i]+=bt[j];
    }
    tot+=wt[i];
}
printf("\n\nProcess\t  Burst Time\t  Waiting Time\t  Turn Around Time");
for(i=0;i<Number_of_Process;i++)
{
    if(priority[i]==0||priority[i]==1)
    tat[i]=bt[i]+wt[i];
    else
        tat[i]=bt[i]+wt[i]-at[i];
    printf("\nP%d \t\t %d\t \t   %d\t\t%d",Process_no[i],bt[i],wt[i],tat[i]);
}
getch();
return 0;
}