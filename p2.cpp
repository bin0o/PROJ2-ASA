/******************************************************************************
 * IST: ASA 2021/22 - P2 - Manuel Albino, Tiago Caldas                        *
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

//------------------------------------------------------------------------------

int v1;
int v2;
int n;
int m;

void readInput(vector<int> reversedGraph[], int m)
{
    for (int i = 0; i < m; i++)
    {
        int x, y;
        assert(scanf("%d %d", &x, &y)==2);
        reversedGraph[y].push_back(x);
    }
}

int validTree(vector<int> reversedGraph[], int n)
{
    for (int v = 1; v <= n; v++)
    {
        if (reversedGraph[v].size() > 2) // node has more than two childs
            return -1;
        for (auto u : reversedGraph[v])
        {
            if (u == v) // looks for cicles
            {
                return -1;
            }
        }
    }
    return 1;
}

int printTree(vector<int> reversedGraph[], int n)
{
    for (int v = 1; v <= n; v++)
    {
        cout << "Head[" << v << "]";
        for (auto u : reversedGraph[v])
        {
            cout << "-> [" << u << "] ";
        }
        printf("\n");
    }
    return 1;
}

void bfs(vector<int> reversedGraph[], vector<int> &ancestors, int pi[], int n, int v){

    int visited[n+1];
    for(int i = 1; i <= n; i++){
        visited[i] = 0;
        pi[i] = 0;
    }
    vector<int> queue;
    queue.push_back(v);
    while (queue.size() != 0){
        int u = queue.front();
        queue.erase(queue.begin());
        for(auto x: reversedGraph[u]){
            if(!visited[x]){
                visited[x] = 1;
                pi[x] = u;
                queue.push_back(x);
                ancestors.push_back(x);
            }   
        }
    }

    for(auto y: ancestors)
        cout << y << "\n";
}

void lca(vector<int> reversedGraph[], int n, int v1, int v2){

    vector<int> ancestorsV1;
    vector<int> ancestorsV2;
    int piV1[n+1];
    int piV2[n+1];

    bfs(reversedGraph,ancestorsV1,piV1, n, v1);
    bfs(reversedGraph,ancestorsV2,piV2, n, v2);



}

//dfs que precisa de levar fix
void dfs(bool visited[],vector<int> adj[], int vertex){
    visited[vertex-1] = true;
    cout << vertex << " ";

    for (int i=0;i<sizeof(adj[vertex-1]) / sizeof(adj[vertex-1][0]);i++)
        if (!visited[adj[vertex-1][i]])
            dfs(visited,adj,adj[vertex-1][i]);
}

int main()
{   
    int v1, v2 , n, m;

    assert(scanf("%d %d", &v1, &v2)==2);
    assert(scanf("%d %d", &n, &m)==2);
    bool visited[n];

    //Inicializar o vetor a falso
    for (int i=0;i<n;i++){
        visited[i]=false;
    }
    
    vector<int> reversedGraph[n + 1];
    readInput(reversedGraph, m);

    if(n < 1 || m < 0 || !validTree(reversedGraph, n))
        cout << "0\n";
    else
        lca(reversedGraph, n, v1, v2);
    
    //dfs(visited,adj,v1);

    return 0;
}