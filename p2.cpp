/******************************************************************************
 * IST: ASA 2021/22 - P2 - Manuel Albino, Tiago Caldas                        *
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#define EDGE_SIZE 2
//------------------------------------------------------------------------------

int v1;
int v2;
int n;
int m;

void readInput(vector<int> adj[], int m)
{
    for (int i = 0; i < m; i++)
    {
        int x, y;
        assert(scanf("%d %d", &x, &y)==2);
        adj[x].push_back(y);
    }
}

int validTree(vector<int> adj[], int n)
{
    for (int v = 1; v <= n; v++)
    {
        if (adj[v].size() > 2) // node has more than two childs
            return -1;
        for (auto u : adj[v])
        {
            if (u == v) // looks for cicles
            {
                return -1;
            }
        }
    }
    return 1;
}

int printTree(vector<int> adj[], int n)
{
    for (int v = 1; v <= n; v++)
    {
        cout << "Head[" << v << "]";
        for (auto u : adj[v])
        {
            cout << "-> [" << u << "] ";
        }
        printf("\n");
    }
    return 1;
}

void lca(vector<int> adj[], int n, int v1, int v2){

}

int main()
{   
    int v1, v2 , n, m;

    assert(scanf("%d %d", &v1, &v2)==2);
    assert(scanf("%d %d", &n, &m)==2);
    vector<int> adj[n + 1];
    readInput(adj, m);

    if(n < 1 || m < 0 || !validTree(adj, n))
        cout << "0\n";
    else
        lca(adj, n, v1, v2);
    printTree(adj,m);

    return 0;
}