#include<iostream>

using namespace std;
int main()
{
    int a[10], b[10], x[10];
    int waiting[10], turnaround[10], completion[10], p[10];
    int i, j, smallest, count = 0, time, n;
    double avg = 0, tt = 0, end;

    n = 5;
  
    a[0] = 0;
    a[1] = 2;
    a[2] = 3;
    a[3] = 5;
    a[4] = 9;
 
    b[0] = 8;
    b[1] = 4;
    b[2] = 2;
    b[3] = 1;
    b[4] = 8;

    p[0] = 0;
    p[1] = 2;
    p[2] = 1;
    p[3] = 3;
    p[4] = 0;
    for(i=0; i<n; i++)
        x[i]=b[i];

    int markT = -1;
    p[9]=99;

    for(time=0; count!=n; time++)
    {
        smallest=9;
        for(i=0; i<n; i++)
        {
            if(a[i]<=time && p[i]<p[smallest] && b[i]>0 )
                smallest=i;
        }
        b[smallest]--;
        markT++;
        cout <<"Process "<< smallest << " had worked " << markT << " times\n ";

        if(b[smallest]==0)
        {
            count++;
            end=time+1;
            completion[smallest] = end;
            waiting[smallest] = end - a[smallest] - x[smallest];
            turnaround[smallest] = end - a[smallest];
        }
    }
    cout<<"Process"<<"\t"<< "burst-time"<<"\t"<<"arrival-time" <<"\t"<<"waiting-time" <<"\t"<<"turnaround-time"<< "\t"<<"completion-time"<<endl;

    for(i=0; i<n; i++)
    {
         cout<<"p"<<i+1<<"\t\t"<<x[i]<<"\t\t"<<a[i]<<"\t\t"<<waiting[i]<<"\t\t"<<turnaround[i]<<"\t\t"<<completion[i]<<"\t\t"<<p[i]<<endl;
        avg = avg + waiting[i];
        tt = tt + turnaround[i];
    }
   cout<<"\n\nAverage waiting time ="<<avg/n;
    cout<<"  Average Turnaround time ="<<tt/n<<endl;
}
