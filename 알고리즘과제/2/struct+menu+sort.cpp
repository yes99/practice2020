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

void bubbleint(int a[], int n)
{
    int flag, t, i, j;

	for (i = 1; i <= n - 1; i++)
	{
		flag = 0;
		for (j = 0; j < n - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
				flag = 1;
			}
		}
		if (flag == 0)
		{
			break;
		}
	}

}

void bubblestring(string a[], int n)
{
    int flag, i, j;
    string t;
	for (i = 1; i <= n - 1; i++)
	{
		flag = 0;
		for (j = 0; j < n - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
				flag = 1;
			}
		}
		if (flag == 0)
		{
			break;
		}
	}
}

void heapint(int heap[], int number)
{
    int i, j, k;
    int c, root;
    int temp;
    //힙구조로 바꾸자
    for(i =1; i <number;i++)
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
}

void heapstring(string heap[], int number)
{
    int i, j, k;
    int c, root;
    string temp;
    //힙구조로 바꾸자
    for(i =1; i <number;i++)
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
}

int main()
{
    music m[100];
    string whole;
    string temp;
    char wholearr[500];
    int i, j, k;
    int structcnt = 0;
    int iptr;
    int insertcnt = 0;
    //ifstream ii("C:\\?��?��?��\\input.txt");
    ifstream ii("finalinput.txt");
    //inputappendtab input
    for (i = 0; i < 10; i++)
    {
        getline(ii, whole);
        strcpy(wholearr, whole.c_str());
        char *ptr = strtok(wholearr, "\t"); // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
        temp = ptr;
        iptr = stoi(temp);
        m[i].rank = iptr;
        cout << ptr << " start" << endl;
        while (ptr != NULL) // 자른 문자열이 나오지 않을 때까지 반복
        {
            // 자른 문자열 출력
            ptr = strtok(NULL, "\t"); // 다음 문자열을 잘라서 포인터를 반환
            if (structcnt == 0)
            {
                temp = ptr;
                cout << ptr << " 0 " << endl;
                m[i].name = temp;
            }
            else if (structcnt == 1)
            {
                temp = ptr;
                cout << ptr << " 1 " << endl;
                m[i].singer = temp;
            }
            else if (structcnt == 2)
            {
                temp = ptr;
                cout << ptr << " 2 " << endl;
                m[i].album = temp;
            }
            else if (structcnt == 3)
            {
                temp = ptr;
                iptr = stoi(temp);
                cout << ptr << " 3 " << endl;
                m[i].like = iptr;
            }
            structcnt++;
        }
        structcnt = 0;
        insertcnt++;
    }
    ii.close();

    for (i = 0; i < 10; i++)
    {
        cout << m[i].rank << " " << m[i].name << " " << m[i].singer << " " << m[i].album << " " << m[i].like << endl;
    }

    int menu;
    int irank, ilike;
    int erank, erase;
    int sortdata, sortmenu;
    string iname, isinger, ialbum;
    cout << "==============================================" << endl;
    while (1)
    {
        cout << "1. INSERT" << endl
             << "2. SORT" << endl
             << "3. ERASE" << endl
             << "4. PRINT" << endl
             << "5. END" << endl;
        cin >> menu;

        if (menu == 1) // insert
        {
            cout << "insert rank, name, singer, album, likes" << endl;
            cout << "rank";
            cin >> irank;
            m[insertcnt].rank = irank;
            cin.ignore();
            cout << "name";
            getline(cin, iname);
            m[insertcnt].name = iname;
            cout << "singer";
            getline(cin, isinger);
            m[insertcnt].singer = isinger;
            cout << "album";
            getline(cin, ialbum);
            m[insertcnt].album = ialbum;
            cout << "like";
            cin >> ilike;
            m[insertcnt].like = ilike;
            insertcnt++;
        }
        else if (menu == 2) //sort
        {
            cout<<"pick the data that you want to sort"<<endl << "1. rank"<<endl<<"2. name of song"<<endl<<"3. singer"<<endl<<"4. album"<<endl<< "5. likes"<<endl;
            cin >>sortdata;
            cout <<"pick how to sort"<<endl <<"1. bubble"<<endl <<"2. heap"<<endl;
            if(sortdata ==1)
            {
                bubbleint(m.rank, insertcnt);
            }
            else if(sortdata ==2)
            {

            }
            else if(sortdata ==3)
            {
                
            }
            else if(sortdata ==4)
            {
                
            }
            else if(sortdata ==5)
            {
                
            }
            else
            {
                cout<<"wrong menu";
            }

        }
        else if (menu == 3) //erase
        {
            int eraseflag = 0;
            cout << "pick the rank of the music that you want to erase";
            cin >> erank;
            //search
            for (i = 0; i < 100; i++)
            {
                if (erank == m[i].rank)
                {
                    erase = i;
                    eraseflag = 1;
                    insertcnt--;
                    break;
                }
            }
            if(eraseflag == 0)
            { 
                 cout << "there's no rank in " << erank << endl;
            }
            else
            {
                for (i = 0; i <= insertcnt; i++)
                {
                    m[erase] = m[erase+1];
                    erase++;
                }
            }
        }
        else if (menu == 4) //print
        {
            cout << "PRINT" << endl;
            for (i = 0; i < insertcnt; i++)
            {
                cout << m[i].rank << " " << m[i].name << " " << m[i].singer << " " << m[i].album << " " << m[i].like << endl;
            }
        }
        else if (menu == 5) //exit
        {
            break;
        }
        else
        {
            cout << "wrong key" << endl;
        }
    }

    return 0;
}

//할일 :: array to string 바꿔주는거 중간에 포함해야함    스트럭트 정리 똑바로 하고  스트럭드테 다 들어가나 똑바로 확인