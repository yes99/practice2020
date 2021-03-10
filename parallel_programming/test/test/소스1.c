// c++ program to implement Shortest Job first

#include <stdio.h>

typedef struct Process
{
    int pid;     // process ID
    int bt;      // burst Time
}Process;


/*
    this function is used for sorting all
    processes in increasing order of burst time
*/
int comparison(Process a, Process b)
{
    return (a.bt < b.bt);
}

// function to find the waiting time for all processes
void findWaitingTime(Process proc[], int n, int wt[])
{
    // waiting time for first process is 0
    wt[0] = 0;

    // calculating waiting time
    for (int i = 1; i < n; i++)
    {
        wt[i] = proc[i - 1].bt + wt[i - 1];
    }
}

// function to calculate turn around time
void findTurnAroundTime(Process proc[], int n, int wt[], int tat[])
{
    // calculating turnaround time by adding bt[i] + wt[i]
    for (int i = 0; i < n; i++)
    {
        tat[i] = proc[i].bt + wt[i];
    }
}

// function to calculate average time
void findAverageTime(Process proc[], int n)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // function to find waiting time of all processes
    findWaitingTime(proc, n, wt);

    // function to find turn around time for all processes
    findTurnAroundTime(proc, n, wt, tat);

    // display processes along with all details
    printf("\nProcesses  Burst time  Waiting time  Turn around time\n");
    // calculate total waiting time and total turn around time
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf(" %d\t\t%d\t%d\t\t%d\n", proc[i].pid, proc[i].bt, wt[t], tat[i]);
    }
    float TWt = total_wt / n;
    float TTt = total_wt / n;
    printf("Average waiting time = %f", TWt);
    printf("\nAverage turn around time = %f", TTt);
}

// main function
int main()
{
    Process proc[] = { {1, 21}, {2, 3}, {3, 6}, {4, 2} };
    int n = sizeof proc / sizeof proc[0];

    // sorting processes by burst time.
    sort(proc, proc + n, comparison);

    printf("Order in which process gets executed\n");

    for (int i = 0; i < n; i++)
    {
        print("%d ", proc[i].pid);
    }

    findAverageTime(proc, n);

    return 0;
}