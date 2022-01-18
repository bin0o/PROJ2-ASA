/******************************************************************************
 * IST: ASA 2021/22 - P2 - Manuel Albino, Tiago Caldas                        *
 ******************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

#define EDGE_SIZE 2
//------------------------------------------------------------------------------

int v1;
int v2;
int n;
int m;

void readInput(vector<int> adj[]) {
    for(int i = 0; i < m; i++){
        int x;
        int y;
        scanf("%d %d", &x, &y);
        adj[x].push_back(y);
    }
}

int verifyTree(vector<int> adj[]){
    for(int v = 1; v <= n; v++){
        for(auto u : adj[v]){
            if (u == v){
                return -1;
            }
        }
        printf("\n");
    }
    return 1;
}

int printTree(vector<int> adj[]){
    for(int v = 1; v <= n; v++){
        cout << "Head[" << v <<"]";
        for(auto u : adj[v]){
            cout << "-> [" << u <<"] ";
        }
        printf("\n");
    }
    return 1;
}

int main() {

    scanf("%d %d", &v1, &v2);
    scanf("%d %d", &n, &m);
    vector<int> adj[n+1];
    readInput(adj);
    verifyTree(adj);

    return 0;
}