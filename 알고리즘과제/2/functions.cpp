#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;
// ii >>
// oo <<
struct music
{
    int rank;
    string name;
    string singer;
    string album;
    int like;
};


void bubblerank(music m[], int n)
{
    int flag, i, j;
    music t;
    for (i = 1; i <= n - 1; i++)
    {
        flag = 0;
        for (j = 0; j < n - i; j++)
        {
            if (m[j].rank > m[j + 1].rank)
            {
                t = m[j];
                m[j] = m[j + 1];
                m[j + 1] = t;
                flag = 1;
            }
        }

        if (flag == 0)
        {
            break;
        }
    }
}

void bubblename(music m[], int n)
{
    int flag, i, j;
    music t;
    for (i = 1; i <= n - 1; i++)
    {
        flag = 0;
        for (j = 0; j < n - i; j++)
        {
            if (m[j].name > m[j + 1].name)
            {
                t = m[j];
                m[j] = m[j + 1];
                m[j + 1] = t;
                flag = 1;
            }
        }

        if (flag == 0)
        {
            break;
        }
    }
}





void bubblesinger(music m[], int n)
{
    int flag, i, j;
    music t;
    for (i = 1; i <= n - 1; i++)
    {
        flag = 0;
        for (j = 0; j < n - i; j++)
        {
            if (m[j].singer > m[j + 1].singer)
            {
                t = m[j];
                m[j] = m[j + 1];
                m[j + 1] = t;
                flag = 1;
            }
        }

        if (flag == 0)
        {
            break;
        }
    }
}
void bubblealbum(music m[], int n)
{
    int flag, i, j;
    music t;
    for (i = 1; i <= n - 1; i++)
    {
        flag = 0;
        for (j = 0; j < n - i; j++)
        {
            if (m[j].album > m[j + 1].album)
            {
                t = m[j];
                m[j] = m[j + 1];
                m[j + 1] = t;
                flag = 1;
            }
        }

        if (flag == 0)
        {
            break;
        }
    }
}

void bubblelike(music m[], int n)
{
    int flag, i, j;
    music t;
    for (i = 1; i <= n - 1; i++)
    {
        flag = 0;
        for (j = 0; j < n - i; j++)
        {
            if (m[j].like > m[j + 1].like)
            {
                t = m[j];
                m[j] = m[j + 1];
                m[j + 1] = t;
                flag = 1;
            }
        }

        if (flag == 0)
        {
            break;
        }
    }
}


void heaprank(music m[], int number)
{
    int i, j, k;
    int c, root;
    music temp;
    //힙구조로 바꾸자
    for(i =1; i <number;i++)
    {
        c = i;
        do
        {
            root = (c-1)/2;
            if(m[root].rank<m[c].rank)
            {
                temp = m[root];
                m[root] = m[c];
                m[c] = temp;
            }
            c = root;
        } while (c!=0 );
    }
//크기를 줄여가며 반복적으로 힙 구성
    for(i = number -1 ; i >=0;i--)
    {
        temp = m[0];
        m[0] = m[i];
        m[i]=temp;
        int root =0;
        int c = 1;
        do
        {
            c = 2 * root +1;
            //자식 중에 더 큰값 찾기
            if(m[c].rank < m[c+1].rank && c < i-1)
            {
                c++;   
            }
            //루트보다 자식이 더 크다면 교환
            if(m[root].rank < m[c].rank && c<i)
            {
                temp = m[root];
                m[root] = m[c];
                m[c]=temp;
            }
            root = c;
        } while (c<i);
    }
}

void heapname(music m[], int number)
{
    int i, j, k;
    int c, root;
    music temp;
    //힙구조로 바꾸자
    for(i =1; i <number;i++)
    {
        c = i;
        do
        {
            root = (c-1)/2;
            if(m[root].name<m[c].name)
            {
                temp = m[root];
                m[root] = m[c];
                m[c] = temp;
            }
            c = root;
        } while (c!=0 );
    }
//크기를 줄여가며 반복적으로 힙 구성
    for(i = number -1 ; i >=0;i--)
    {
        temp = m[0];
        m[0] = m[i];
        m[i]=temp;
        int root =0;
        int c = 1;
        do
        {
            c = 2 * root +1;
            //자식 중에 더 큰값 찾기
            if(m[c].name < m[c+1].name && c < i-1)
            {
                c++;   
            }
            //루트보다 자식이 더 크다면 교환
            if(m[root].name < m[c].name && c<i)
            {
                temp = m[root];
                m[root] = m[c];
                m[c]=temp;
            }
            root = c;
        } while (c<i);
    }
}

void heapsinger(music m[], int number)
{
    int i, j, k;
    int c, root;
    music temp;
    //힙구조로 바꾸자
    for(i =1; i <number;i++)
    {
        c = i;
        do
        {
            root = (c-1)/2;
            if(m[root].singer<m[c].singer)
            {
                temp = m[root];
                m[root] = m[c];
                m[c] = temp;
            }
            c = root;
        } while (c!=0 );
    }
//크기를 줄여가며 반복적으로 힙 구성
    for(i = number -1 ; i >=0;i--)
    {
        temp = m[0];
        m[0] = m[i];
        m[i]=temp;
        int root =0;
        int c = 1;
        do
        {
            c = 2 * root +1;
            //자식 중에 더 큰값 찾기
            if(m[c].singer < m[c+1].singer && c < i-1)
            {
                c++;   
            }
            //루트보다 자식이 더 크다면 교환
            if(m[root].singer < m[c].singer && c<i)
            {
                temp = m[root];
                m[root] = m[c];
                m[c]=temp;
            }
            root = c;
        } while (c<i);
    }
}

void heapalbum(music m[], int number)
{
    int i, j, k;
    int c, root;
    music temp;
    //힙구조로 바꾸자
    for(i =1; i <number;i++)
    {
        c = i;
        do
        {
            root = (c-1)/2;
            if(m[root].album<m[c].album)
            {
                temp = m[root];
                m[root] = m[c];
                m[c] = temp;
            }
            c = root;
        } while (c!=0 );
    }
//크기를 줄여가며 반복적으로 힙 구성
    for(i = number -1 ; i >=0;i--)
    {
        temp = m[0];
        m[0] = m[i];
        m[i]=temp;
        int root =0;
        int c = 1;
        do
        {
            c = 2 * root +1;
            //자식 중에 더 큰값 찾기
            if(m[c].album < m[c+1].album && c < i-1)
            {
                c++;   
            }
            //루트보다 자식이 더 크다면 교환
            if(m[root].album < m[c].album && c<i)
            {
                temp = m[root];
                m[root] = m[c];
                m[c]=temp;
            }
            root = c;
        } while (c<i);
    }
}

void heaplike(music m[], int number)
{
    int i, j, k;
    int c, root;
    music temp;
    //힙구조로 바꾸자
    for(i =1; i <number;i++)
    {
        c = i;
        do
        {
            root = (c-1)/2;
            if(m[root].rank<m[c].rank)
            {
                temp = m[root];
                m[root] = m[c];
                m[c] = temp;
            }
            c = root;
        } while (c!=0 );
    }
//크기를 줄여가며 반복적으로 힙 구성
    for(i = number -1 ; i >=0;i--)
    {
        temp = m[0];
        m[0] = m[i];
        m[i]=temp;
        int root =0;
        int c = 1;
        do
        {
            c = 2 * root +1;
            //자식 중에 더 큰값 찾기
            if(m[c].rank < m[c+1].rank && c < i-1)
            {
                c++;   
            }
            //루트보다 자식이 더 크다면 교환
            if(m[root].rank < m[c].rank && c<i)
            {
                temp = m[root];
                m[root] = m[c];
                m[c]=temp;
            }
            root = c;
        } while (c<i);
    }
}








int main()
{
    music m[100];
    m[0] = {1, "sdfsdf", "dsagsag", "wegwegewg", 15};
    m[1] = {15, "gagewgew", "wegewgewg", "ewfwgewg", 23};
    m[2] = {13, "rehrehhahreah", "gewgewgwghjh", "gjghgg,gh,gh", 1};
    heapsinger(m, 3);
    for (int i = 0; i < 3; i++)
    {
        cout << m[i].rank << "\t" << m[i].name << "\t" << m[i].album << "\t" << m[i].singer << "\t" << m[i].rank << endl;
    }
}