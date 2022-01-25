/******************************************************************************
 * IST: ASA 2021/22 - P2 - Manuel Albino, Tiago Caldas                        *
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <cassert>
#include <queue>

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

bool isCyclicAux(vector<int> reversedGraph[],int pile[],int visited[],int vertex){
    if (!visited[vertex]){
        visited[vertex]=1;
        pile[vertex]=1;

        for (auto x:reversedGraph[vertex]){
            if(!visited[x] && isCyclicAux(reversedGraph,pile,visited,x))
                return true;
            else if(pile[x])
                return true;
        }
    }
    pile[vertex]=0;
    return false;
}

bool isCyclic(vector<int> reversedGraph[], int n)
{
    // Mark all the vertices as not visited
    int visited[n+1];
    int pile[n+1];
    for(int i = 1; i <= n; i++){
        visited[i] = 0;
        pile[i]=0;
    }
    for (int i =1;i<=n;i++)
        return isCyclicAux(reversedGraph,pile,visited,i);   
}




int main()
{   
    int v1, v2 , n, m;

    assert(scanf("%d %d", &v1, &v2)==2);
    assert(scanf("%d %d", &n, &m)==2);
    
    vector<int> reversedGraph[n + 1];
    readInput(reversedGraph, m);

    if(n < 1 || m < 0 || isCyclic(reversedGraph, n))
        cout << "entrou\n";

    return 0;
}