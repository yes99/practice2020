#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#DEFINE ARRAYSIZE 5
using namespace std;

typedef struct process{
    int pid;
    int arr_time;
    int bur_time;
    int pri;
    int rank;
}Process;


void printVec(deque<int> procs){
    cout << '<';
    for(int i = 0; i < procs.size() ; i++){
        cout << procs[i] << ' ';
    }
    cout << ">\n";
}


int main(){


    Process procs[ARRSIZE];
    // pid arival_time burst_time priority rank
    procs[0] = {0, 0, 8, 0, 0};
    procs[1] = {1, 2, 4, 2, 0};
    procs[2] = {2, 3, 2, 1, 0};
    procs[3] = {3, 5, 1, 3, 0};
    procs[4] = {4, 9, 8, 0, 0};
    deque<int> procs = {8, 4, 2, 1, 8};

    printVec(procs);
    int time = 0;

    while(procs.size() > 0){
        int curr = procs.front();
        procs.pop_front();
        curr--;
        time++;
        if (curr != 0){
            procs.push_back(curr);
            printf("proc[%d] has worked at %d ms\n", curr, time);
        }
        printVec(procs);
    }
    return 0;
}