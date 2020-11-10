#include<iostream>

 using namespace std;
int main()
{
    int arr_time[10],bur_time[10],origin_bur[10];
    int waiting[10],turnaround[10],completion[10],pri[10];
    int i,j,smallest,count=0,time,n;
    double avg=0,tt=0,end;

   cout<<"\nEnter the number of Processes: ";
    cin>>n;
    for(i=0;i<n;i++)
    {
      cout<<"\nEnter arrival time of process: ";
      cin>>arr_time[i];
    }
    for(i=0;i<n;i++)
    {
      cout<<"\nEnter burst time of process: ";
      cin>>bur_time[i];
    }
    for(i=0;i<n;i++)
    {
      cout<<"\nEnter priority of process: ";
      cin>>pri[i];
    }
    for(i=0; i<n; i++)
        origin_bur[i]=bur_time[i];

    int markT = 0;
    pri[9]=9999;
    for(time=0; count!=n; time++)
    {
        smallest=9;
        for(i=0; i<n; i++)
        {
            if(arr_time[i]<=time && pri[i]<pri[smallest] && bur_time[i]>0 )
                smallest=i;
        }
        bur_time[smallest]--;
        markT++;
        cout <<"Process "<< smallest << " had worked " << markT << " times\n ";

        if(bur_time[smallest]==0)
        {
            count++;
            end=time+1;
            completion[smallest] = end;
            waiting[smallest] = end - arr_time[smallest] - origin_bur[smallest];
            turnaround[smallest] = end - arr_time[smallest];
            cout <<"Process "<< smallest << " had worked " << markT << " times\n ";
        }
    }
    cout<<"Process"<<"\t"<< "burst-time"<<"\t"<<"arrival-time" <<"\t"<<"waiting-time" <<"\t"<<"turnaround-time"<< "\t"<<"completion-time"<<endl;

    for(i=0; i<n; i++)
    {
         cout<<"pri"<<i+1<<"\t\t"<<origin_bur[i]<<"\t\t"<<arr_time[i]<<"\t\t"<<waiting[i]<<"\t\t"<<turnaround[i]<<"\t\t"<<completion[i]<<"\t\t"<<pri[i]<<endl;
        avg = avg + waiting[i];
        tt = tt + turnaround[i];
    }
   cout<<"\n\nAverage waiting time ="<<avg/n;
    cout<<"  Average Turnaround time ="<<tt/n<<endl;
}
