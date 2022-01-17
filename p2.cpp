/******************************************************************************
 * IST: ASA 2021/22 - P2 - Manuel Albino, Tiago Caldas                        *
 ******************************************************************************/
#include <iostream>

using namespace std;

#define EDGE_SIZE 2
//------------------------------------------------------------------------------

int v1;
int v2;
int n;
int m;

void readInput(int(&graph) [][EDGE_SIZE]) {


}

int main() {

    cin >> v1 >> v2;
    cin >> n >> m;
    int graph[m][EDGE_SIZE];
    readInput(graph);

    return 0;
}