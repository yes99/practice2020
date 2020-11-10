#include <cstdio>
#include <algorithm>

#define ARRSIZE 5

typedef struct process{
    int pid;
    int arr_time;
    int bur_time;
    int pri;
    int rank;
}Process;

typedef struct process_result{
    int processing_time;
    int wait_time; 
    int compl_time;
    int AWaiting_time;
    int ATa_time;

}result;


/*
Process makeProcess(int pid, int arrive, int burst, int pri)
{
    Process p;
    p.pid = pid;
    p.arr_time = arrive;
    p.bur_time = burst;
    p.pri = pri;

    return p;
}*/

bool compareArrivetime(Process left, Process right)
{
    return left.arr_time < right.arr_time;
}

bool compareBursttime(Process left, Process right)
{
    return left.bur_time < right.bur_time;
}

bool comparePid(Process left, Process right)
{
    return left.pid < right.pid;
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
    Process procs[ARRSIZE];
    // pid arival_time burst_time priority rank
    procs[0] = {0, 0, 8, 0, 0};
    procs[1] = {1, 2, 4, 2, 0};
    procs[2] = {2, 3, 2, 1, 0};
    procs[3] = {3, 5, 1, 3, 0};
    procs[4] = {4, 9, 8, 0, 0};

    printProcessArray(procs, ARRSIZE);
   
    std::sort(procs, procs+5, compareArrivetime);
    printf("##################### Change Arrive\n");
    printProcessArray(procs, ARRSIZE);

   

    for(int i = 0; i < ARRSIZE; i++)
    {
        procs[i].rank = i;
    }
    printf("##################### Input Rank\n");
    printProcessArray(procs, ARRSIZE);

    std::sort(procs, procs+5, comparePid);

    printf("#####################\n");    
    printProcessArray(procs, ARRSIZE);

    //arrive 타임을 비교해서 나열?
    //걔네를 순서대로 나열하자. 
    //나열을 하는 과정에서 다 더해야함?
    //필요한것 : wait_time  complete_time, average_wait_time, average_turnaround_time
    int wt[ARRSIZE]; 
    int awt;
    int tt[ARRSIZE];
    int att;
    int sum_wt = 0, sum_tt = 0;
    int ct[ARRSIZE];
    ct[0] = procs[0].bur_time;

    for(int i =1; i < ARRSIZE; i++)
    {
        ct[i] = ct[i-1] + procs[i].bur_time;
    }

    for(int j = 0; j < ARRSIZE; j++)
    {
        tt[j] = ct[j] - procs[j].bur_time;
    }

    for(int k = 0; k < ARRSIZE; k++)
    {
        wt[k] = ct[k] - procs[k].bur_time - procs[k].arr_time;
    }

    for(int l = 0; l < ARRSIZE; l++)
    {
        sum_wt = sum_wt + wt[l];
    }

    for (int m = 0; m < ARRSIZE ; m++)
    {
        sum_tt = sum_tt + tt[m]; 
    }

    printFinalProcessArray(procs,ARRSIZE, wt, ct);
    printf("\n Average Waiting time : %d", sum_wt/ARRSIZE);
    printf("\n Average Turnaround time% : %d", sum_tt/ARRSIZE);
    
/*
    ct = ct + //arrivetime
    tt = ct - Process.arr_time;//arrivetime
    wt = ct - Process.bur_time - Process.arr_time//bursttime - arrivetime
*/

}