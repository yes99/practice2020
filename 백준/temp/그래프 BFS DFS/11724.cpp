#include <iostream>
#include <vector>
using namespace std;
const int MAX = 1000 + 1;
int M, N;
vector<int> graph[MAX];
bool visited[MAX];
//전형적인 DFS
void DFS(int node)
{
    visited[node] = true;
    for (int i = 0; i < graph[node].size(); i++)
    {
        int next = graph[node][i];
        //node에 연결된 다른 정점을 모두 방문
        //이미 방문했다면 방문하지 않는다
        if (!visited[next])
            DFS(next);
    }
}

int main(void)
{
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int node1, node2;
        cin >> node1 >> node2;
        //undirected graph
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }
    int cnt = 0;
    for (int i = 1; i <= N; i++)
        if (!visited[i])
        {
            DFS(i);
            cnt++;
        }
    cout << cnt << endl;
    return 0;
}