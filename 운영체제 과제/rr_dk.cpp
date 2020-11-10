#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#define ARRAYSIZE 5

using namespace std;

typedef struct process{
    int pid;
    int arr_time;
    int bur_time;
    int pri;

}Process;


void printVec(deque<int> procs){
    cout << '<';
    for(int i = 0; i < procs.size() ; i++){
        cout << procs[i] << ' ';
    }
    cout << ">\n";
}


int main(){


    Process procs[ARRAYSIZE];
    // pid arival_time burst_time priority rank
 
    deque<Process> = {8, 4, 2, 1, 8};

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