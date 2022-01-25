/******************************************************************************
 * IST: ASA 2021/22 - P2 - Manuel Albino, Tiago Caldas                        *
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <algorithm>

using namespace std;

//------------------------------------------------------------------------------

unordered_map<int,int> seenv2;
unordered_map<int,int> common_seen;

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

bool checksCyclesInNode(vector<int> reversedGraph[],int pile[],int visited[],int vertex){
    if (!visited[vertex]){
        visited[vertex]=1;
        pile[vertex]=1;

        for (auto x:reversedGraph[vertex]){
            if(!visited[x] && checksCyclesInNode(reversedGraph,pile,visited,x))
                return true;
            else if(pile[x])
                return true;
        }
    }
    pile[vertex]=0;
    return false;
}

bool validTree(vector<int> reversedGraph[], int n)
{
    int visited[n+1];
    int pile[n+1];
    for(int i = 1; i <= n; i++){
        visited[i] = 0;
        pile[i]=0;
    }
    for (int v = 1; v <= n; v++)
    {
        if (reversedGraph[v].size() > 2) // node has more than two parents
            return false;
        if (checksCyclesInNode(reversedGraph,pile,visited,v))
            return false;
    }
    return true;
}

void bfs1(vector<int> reversedGraph[], vector<int> &ancestors, int pi[], int n, int v){

    int visited[n+1];
    for(int i = 1; i <= n; i++){
        visited[i] = 0;
        pi[i] = 0;
    }
    ancestors.push_back(v);
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
}

void bfs2(vector<int> reversedGraph[], vector<int> &ancestors, int pi[], int n, int v){

    int visited[n+1];
    for(int i = 1; i <= n; i++){
        visited[i] = 0;
        pi[i] = 0;
    }
    ancestors.push_back(v);
    seenv2[v] = 1;
    vector<int> queue;
    queue.push_back(v);
    while (queue.size() != 0){
        int u = queue.front();
        queue.erase(queue.begin());
        for(auto x: reversedGraph[u]){
            if(!visited[x]){
                seenv2[x] = 1;
                visited[x] = 1;
                pi[x] = u;
                queue.push_back(x);
                ancestors.push_back(x);
            }   
        }
    }
}

void lca(vector<int> reversedGraph[], int n, int v1, int v2){

    vector<int> ancestorsV1;
    vector<int> ancestorsV2;
    vector<int> common_ancestors;

    int piV1[n+1];
    int piV2[n+1];

    bfs1(reversedGraph,ancestorsV1,piV1, n, v1);
    bfs2(reversedGraph,ancestorsV2,piV2, n, v2);

    for(auto x: ancestorsV1){
        if(seenv2[x]){
            common_ancestors.push_back(x);
            common_seen[x] = 1;
        }
    }
    int size = common_ancestors.size();
    if(size == 0)
        cout << "-\n";
    else{
        sort(common_ancestors.begin(), common_ancestors.end());
        for(auto x: common_ancestors){
            if(!common_seen[piV1[x]] && !common_seen[piV2[x]])
                cout << x << " ";
        }
        cout << endl;
    }
}

int main()
{   
    int v1, v2 , n, m;

    assert(scanf("%d %d", &v1, &v2)==2);
    assert(scanf("%d %d", &n, &m)==2);
    
    vector<int> reversedGraph[n+1];
    readInput(reversedGraph, m);

    if(n < 1 || m < 0 || !validTree(reversedGraph, n))
        cout << "0\n";
    else
        lca(reversedGraph, n, v1, v2);

    return 0;
}