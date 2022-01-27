/******************************************************************************
 * IST: ASA 2021/22 - P2 - Manuel Albino, Tiago Caldas                        *
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <algorithm>
#include <queue>

using namespace std;

//------------------------------------------------------------------------------

int v1, v2 , n, m;
vector<vector<int>> reversedGraph;


vector<int> visitedInIteration;
vector<int> visited;


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

bool checksCyclesInNode(int v){
    if (!visited[v]){
        visited[v]=1;
        visitedInIteration[v]=1;

        for (auto x:reversedGraph[v]){
            if(!visited[x] && checksCyclesInNode(x))
                return true;
            else if(visitedInIteration[x]) //terminal case
                return true;
        }
    }
    //puts every v that he has passed to 0 in visitedInIteration
    visitedInIteration[v]=0;
    return false;
}

bool validTree()
{
    visited.resize(n+1,0);
    visitedInIteration.resize(n+1,0);
    for (int v = 1; v <= n; v++)
    {
        if (reversedGraph[v].size() > 2) // node has more than two parents
            return false;
        if (checksCyclesInNode(v))
            return false;
    }
    return true;
}

void bfs(vector<vector<int>> &pi, vector<int> &visitedV1, vector<int> &ancestorsV1){
    visitedV1[v1] = 1;
    ancestorsV1[v1]=1;
    queue<int> queue;
    queue.push(v1);
    while (!queue.empty()){
        int u = queue.front();
        queue.pop();
        for(auto x: reversedGraph[u]){
            pi[x].push_back(u);
            if(!visitedV1[x]){
                visitedV1[x] = 1;
                queue.push(x);
                ancestorsV1[x]=1;
            }
        }
    }
}

void bfs2(vector<int> &common_ancestors,vector<vector<int>> &pi,unordered_map<int,int> &common_seen, vector<int> &visitedV2, vector<int> &ancestorsV1){
    visitedV2[v2] = 1;
    if(ancestorsV1[v2]){
        common_ancestors.push_back(v2);
        common_seen[v2]=1;
    }
    queue<int> queue;
    queue.push(v2);
    while (!queue.empty()){
        int u = queue.front();
        queue.pop();
        for(auto x: reversedGraph[u]){
            pi[x].push_back(u);
            if(!visitedV2[x]){
                visitedV2[x] = 1;
                queue.push(x);
                if (ancestorsV1[x]){
                    common_seen[x]=1;
                    common_ancestors.push_back(x);
                    
                }
            }
        }
    }
}

void lca(){
    
    vector<int> ancestorsV1(n+1,0);
    vector<int> visitedV1(n+1,0);
    vector<int> visitedV2(n+1,0);
    vector<int> common_ancestors;
    vector<vector<int>> pi(n+1);
    unordered_map<int,int> common_seen;

    bfs(pi,visitedV1,ancestorsV1);
    bfs2(common_ancestors,pi,common_seen,visitedV2,ancestorsV1);

    int size = common_ancestors.size();
    if(size == 0)
        cout << "-\n";
    else{
        sort(common_ancestors.begin(), common_ancestors.end());
        for(auto x: common_ancestors){
            int flag = 0;
            for(auto v: pi[x]){
                if(common_seen[v]){
                    flag = 1;
                    break;
                }
            }
            if(!flag)
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
        lca();
    return 0;
}