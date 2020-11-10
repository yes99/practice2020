#include<iostream>

using namespace std;
int main()
{
    int arr_time[10],bur_time[10],origin_bur[10];
    int waiting[10],turnaround[10],completion[10];
    int i,j,smallest,count=0,time,n;
    double avg=0,tt=0,end; 

    cout<<"\nEnter the number of Processes: ";  //input
    cin>>n;
    for(i=0; i<n; i++)
    {
        cout<<"\nEnter arrival time of process: ";  //input
        cin>>arr_time[i];
    }
    for(i=0; i<n; i++)
    {
        cout<<"\nEnter burst time of process: ";  //input
        cin>>bur_time[i];
    }
    for(i=0; i<n; i++)
        origin_bur[i]=bur_time[i];
    int markT = -1;
    bur_time[9]=9999;
    for(time=0; count!=n; time++)
    {
        smallest=9;
        for(i=0; i<n; i++)
        {
            if(arr_time[i]<=time && bur_time[i]<bur_time[smallest] && bur_time[i]>0 )
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

        }
    }
    cout<<"Process"<<"\t"<< "burst-time"<<"\t"<<"arrival-time" <<"\t"<<"waiting-time" <<"\t"<<"turnaround-time"<< "\t"<<"completion-time"<<endl;
    for(i=0; i<n; i++)
    {
        cout<<"p["<<i<<"]\t\t"<<origin_bur[i]<<"\t\t"<<arr_time[i]<<"\t\t"<<waiting[i]<<"\t\t"<<turnaround[i]<<"\t\t"<<completion[i]<<endl;
        avg = avg + waiting[i];
        tt = tt + turnaround[i];
    }
    cout<<"\n\nAverage waiting time ="<<avg/n;
    cout<<"  Average Turnaround time ="<<tt/n<<endl;
}