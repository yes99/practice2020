#include<iostream>

using namespace std;
int main()
{
    int arr_time[10];
    int bur_time[10];
    int origin_bur[10];
    int pri[10];
    int wt[10], tt[10], ct[10];
    int i, j, smallest, count = 0, time, n;
    double sum_wt = 0, sum_tt = 0, complete;

    cout << "Enter the number of Processes: ";  
    cin >> n;
    for (i = 0; i < n; i++)
    {
        cout << "Enter arrival time of process: ";  
        cin >> arr_time[i];
    }
    for (i = 0; i < n; i++)
    {
        cout << "Enter burst time of process: ";  
        cin >> bur_time[i];
    }
    for(i=0;i<n;i++)
    {
      cout<<"Enter priority of process: ";
      cin>>pri[i];
    }
    for (i = 0; i < n; i++)
    {
        origin_bur[i] = bur_time[i];
    }
    int markT = 0;
    bur_time[9] = 9999;
    for (time = 0; count != n; time++)
    {
        smallest = 9;
        for (i = 0; i < n; i++)
        {
            if (arr_time[i] <= time && bur_time[i] < bur_time[smallest] && bur_time[i]>0)
                smallest = i;
        }
        bur_time[smallest]--;
        markT++;
        cout << "Process " << smallest << " had worked " << markT << " times\n ";

        if (bur_time[smallest] == 0)
        {
            count++;
            complete = time + 1;
            ct[smallest] = complete;
            wt[smallest] = complete - arr_time[smallest] - origin_bur[smallest];
            tt[smallest] = complete - arr_time[smallest];

        }
    }
    cout << "Process" << "\t" << "burst-time" << "\t" << "arrival-time" << "\t" << "wt-time" << "\t" << "tt-time" << "\t" << "ct-time" << endl;
    for (i = 0; i < n; i++)
    {
        cout << "p[" << i << "]\t\t" << origin_bur[i] << "\t\t" << arr_time[i] << "\t\t" << wt[i] << "\t\t" << tt[i] << "\t\t" << ct[i] << endl;
        sum_wt = sum_wt + wt[i];
        sum_tt = sum_tt + tt[i];
    }
    cout << "\n\nAverage wt time =" << sum_wt / n;
    cout << "  Average tt time =" << sum_tt / n << endl;
}