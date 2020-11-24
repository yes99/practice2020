#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;
// ii >>
// oo <<
struct music{
    int rank;
    string name;
    string singer;
    string album;
    int like;
};

int number = 9;
int heap[9] = {7,6,5,8,3,5,9,1,6};


int main()
{
    int i, j, k;
    int c, root;
    int temp;
    //힙구조로 바꾸자
    for( i =1; i <number;i++)
    {
        c = i;
        do
        {
            root = (c-1)/2;
            if(heap[root]<heap[c])
            {
                temp = heap[root];
                heap[root] = heap[c];
                heap[c] = temp;
            }
            c = root;
        } while (c!=0 );
    }
//크기를 줄여가며 반복적으로 힙 구성
    for(i = number -1 ; i >=0;i--)
    {
        temp = heap[0];
        heap[0] = heap[i];
        heap[i]=temp;
        int root =0;
        int c = 1;
        do
        {
            c = 2 * root +1;
            //자식 중에 더 큰값 찾기
            if(heap[c] < heap[c+1] && c < i-1)
            {
                c++;   
            }
            //루트보다 자식이 더 크다면 교환
            if(heap[root] < heap[c] && c<i)
            {
                temp = heap[root];
                heap[root] = heap[c];
                heap[c]=temp;
            }
            root = c;
        } while (c<i);
        
    }
    for( i = 0 ; i <number ; i++)
    {
        cout << heap[i] << " ";
    }
}