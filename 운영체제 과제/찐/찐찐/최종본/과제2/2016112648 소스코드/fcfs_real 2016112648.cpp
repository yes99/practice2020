#include <cstdio>
#include <algorithm>

typedef struct process{
    int pid;
    int arr_time;
    int bur_time;
    int pri;
    int rank;
}Process;

bool compareArrivetime(Process left, Process right)
{
    return left.arr_time < right.arr_time;
}

bool comparePid(Process left, Process right)
{
    return left.pid < right.pid;
}

bool compareRank(Process left, Process right)
{
    return left.rank < right.rank;
}

void printProcess(Process a)
{
    printf("Process[%d] <arr = %d, bur = %d, pri = %d, rank = %d>\n", a.pid, a.arr_time, a.bur_time, a.pri, a.rank);
}

void printProcessArray(Process* arr, int size)
{
    for(int i=0; i < size; i++)
    {
        printProcess(arr[i]);
    }

}

void printFinalProcess(Process a, int* wt, int* ct)
{
    printf("Process[%d] wt = %d, ct = %d\n", a.pid, wt[a.rank],ct[a.rank] );
}

void printFinalProcessArray(Process* arr, int size, int* wt, int* ct)
{
    for(int i=0; i < size; i++)
    {
        printFinalProcess(arr[i], wt,  ct);
    }

}

int main()
{
    int n;

    printf("input the number of the process");
    scanf("%d", &n);

    Process procs[n];

    for(int i=0; i<n; i++)
    {
        procs[i].pid = i;
        procs[i].rank = 0;
    }
    printf("input process arrival time , burst time , and priority\n");
    for(int i=0; i<n; i++)
    {
        printf("Process num[%d] :", i);
        scanf("%d", &procs[i].arr_time );
        scanf("%d", &procs[i].bur_time);
        scanf("%d", &procs[i].pri);
    }
    printf("#####################default\n");
    printProcessArray(procs, n);
   
    std::sort(procs, procs+5, compareArrivetime);
    printf("#####################sort arrive\n");
    printProcessArray(procs, n);
    for(int i = 0; i < n; i++)
    {
        procs[i].rank = i;
    }
    printf("#####################put rank\n");
    printProcessArray(procs, n);

    int wt[n]; 
    int awt;
    int tt[n];
    int att;
    float sum_wt = 0.0, sum_tt = 0.0;
    int ct[n];
    ct[0] = procs[0].bur_time;

    for(int i =1; i < n; i++)
    {
        ct[i] = ct[i-1] + procs[i].bur_time;
    }

    for(int j = 0; j < n; j++)
    {
        tt[j] = ct[j] - procs[j].bur_time;
    }

    for(int k = 0; k < n; k++)
    {
        wt[k] = ct[k] - procs[k].bur_time - procs[k].arr_time;
    }

    for(int l = 0; l < n; l++)
    {
        sum_wt = sum_wt + wt[l];
    }

    for (int m = 0; m < n ; m++)
    {
        sum_tt = sum_tt + tt[m]; 
    }

    printf("=========================================\n");
    printf("processing time\n");
    printf("process[%d] worked %d to %d\n", procs[0].pid, procs[0].arr_time, ct[0]);
    for (int i=1; i<n ;i++)
    {
        printf("process[%d] worked %d to %d\n", procs[i].rank, ct[i-1], ct[i]);
    }

    printf("=========================================\n");
    printFinalProcessArray(procs,n, wt, ct);
    printf("=========================================\n");
    printf("\n Average Waiting time : %f", sum_wt/n);
    printf("\n Average Turnaround time% : %f", sum_tt/n);
}