#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

struct Process
{
    int pid;
    int arrTime;
    int burTime;
    int pri;

    void print()
    {
        cout << "pid = " <<pid << ", arrive time = " << arrTime << '\n';
    }
};

int main()
{

    Process procsArr[5];
     //   pid||arival_time||burst_time||priority rank
    procsArr[0] = {0, 0, 8, 0};
    procsArr[1] = {1, 2, 4, 2};
    procsArr[2] = {2, 3, 2, 1};
    procsArr[3] = {3, 5, 1, 3};
    procsArr[4] = {4, 9, 8, 0};

    deque<Process> procs;
    //비교해서 넣어라
  
    int t = 1;
   

    while (procs.size() >= 0)
    {
        for (Process e : procsArr)
        { //프로세스 단위로 쭉 순회한다
            if (e.arrTime == t)
            {
                procs.push_back(e);
            }
        }

        if (procs.size() == 0)
        {
            break;
        }

        Process curr = procs.front();
        procs.pop_front();
        curr.burTime--;
        cout <<"pid " << curr.pid << " worked at " << t <<"\n";

        if (curr.burTime != 0)
        {
            procs.push_back(curr); // 하나 옮겨라
        }
        else
        {
            curr.print();
            cout <<"pid " <<curr.pid << " is done! at time " << t << "\n\n";

        }
        t++;
    }
    cout << "END" << endl;

    return 0;
}