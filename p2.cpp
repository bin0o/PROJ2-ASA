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

int v1, v2 , n, m;
vector<vector<int>> reversedGraph;

void readInput()
{   
    reversedGraph.resize(n+1);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        assert(scanf("%d %d", &x, &y)==2);
        reversedGraph[y].push_back(x);
    }
}

bool checksCyclesInNode(vector<int> &visitedInRecursion,vector<int> &visited,int vertex){
    if (!visited[vertex]){
        visited[vertex]=1;
        visitedInRecursion[vertex]=1;

        for (auto x:reversedGraph[vertex]){
            if(!visited[x] && checksCyclesInNode(visitedInRecursion,visited,x))
                return true;
            else if(visitedInRecursion[x]) //terminal case
                return true;
        }
    }
    //puts every vertex that he has passed to 0 in visitedInRecursion
    visitedInRecursion[vertex]=0;
    return false;
}

bool validTree()
{
    vector<int> visited(n+1,0);
    vector<int> visitedInRecursion(n+1,0);
    for (int v = 1; v <= n; v++)
    {
        if (reversedGraph[v].size() > 2) // node has more than two parents
            return false;
        if (checksCyclesInNode(visitedInRecursion,visited,v))
            return false;
    }
    return true;
}

void bfs(vector<int> &ancestors, vector<int> &pi, vector<int> &visited, int v){
    visited[v] = 1;
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

void lca(int v1, int v2){

    unordered_map<int,int> common_seen;
    vector<int> ancestorsV1;
    vector<int> ancestorsV2;
    vector<int> common_ancestors;

    vector<int> piV1(n+1,0);
    vector<int> piV2(n+1,0);
    
    vector<int> visitedV1(n+1,0);
    vector<int> visitedV2(n+1,0);

    bfs(ancestorsV1,piV1,visitedV1, v1);
    bfs(ancestorsV2,piV2,visitedV2, v2);

    for(auto x: ancestorsV1){
        if(visitedV2[x]){
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
    assert(scanf("%d %d", &v1, &v2)==2);
    assert(scanf("%d %d", &n, &m)==2);
    
    readInput();

    if(n < 1 || m < 0 || !validTree())
        cout << "0\n";
    else
        lca(v1, v2);

    return 0;
}