#include<iostream>

 using namespace std;
int main()
{
    int arr_time[10];
    int bur_time[10];
    int origin_bur[10];
    int pri[10];
    int wt[10],tt[10],ct[10];
    int i,j,smallest=0,count=0,time,n, complete; //i j 를 너무 많이 써야해서 미리 선언
    float sum_avg=0,sum_tt=0; 
  
   cout<<"Enter the number of Processes: ";
    cin>>n;
    for(i=0;i<n;i++)
    {
      cout<<"Enter arrival time of process: ";
      cin>>arr_time[i];
    }
    for(i=0;i<n;i++)
    {
      cout<<"Enter burst time of process: ";
      cin>>bur_time[i];
    }
    for(i=0;i<n;i++)
    {
      cout<<"Enter priority of process: ";
      cin>>pri[i];
    }
    for(i=0; i<n; i++)
    {
      origin_bur[i]=bur_time[i];
    }
    int markT = 0;
    pri[9]=9999;
    for(time=0; count!=n; time++)
    {
        cout <<"Process "<< smallest << " had worked " << markT << " times\n ";
        smallest=9;
        for(i=0; i<n; i++)
        {
            if(arr_time[i]<=time && pri[i]<pri[smallest] && bur_time[i]>0 )
                smallest=i;
        }
        bur_time[smallest]--;
        markT++;

        if(bur_time[smallest]==0)
        {
            count++;
            complete=time+1;
            ct[smallest] = complete;
            wt[smallest] = complete - arr_time[smallest] - origin_bur[smallest];
            tt[smallest] = complete - arr_time[smallest];
            cout <<"Process "<< smallest << " had worked " << markT << " times\n ";
        }
    }
    cout<<"Process"<<"\t"<< "burst-time"<<"\t"<<"arrival-time" <<"\t"<<"waiting-time" <<"\t"<<"turnaround-time"<< "\t"<<"complete-time"<<"\t" << "priority" <<endl;

    for(i=0; i<n; i++)
    {
        cout<<"pro["<<i<<"]\t\t"<<origin_bur[i]<<"\t\t"<<arr_time[i]<<"\t\t"<<wt[i]<<"\t\t"<<tt[i]<<"\t\t"<<ct[i]<<"\t\t"<<pri[i]<<endl;
        sum_avg = sum_avg + wt[i];
        sum_tt = sum_tt + tt[i];
    }
   cout<<"\n\nAverage waiting time ="<<sum_avg/n;
    cout<<"  Average Turnaround time ="<<sum_tt/n<<endl;
}
