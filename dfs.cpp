#include "Dfs.h"

// Constructor - init the dfs
Dfs::Dfs(Graph* graph) {
    originalGraph = graph;
    int n = graph->getNumOfVertices();
    color = (eVerticesDfsStatus*)calloc(n + 1, sizeof(eVerticesDfsStatus));
    startList.reserve(n);
    endList.reserve(n);
    dfsGraph = Graph(n);
    mainDfs();
}

// main loop of the dfs
void Dfs::mainDfs() {
    int n = originalGraph->getNumOfVertices();
    for (int i = 1; i <= n; i++) {
        if (color[i] == eVerticesDfsStatus::WHITE)
            visit(i);
    }
}

// visit recursive function
void Dfs::visit(int vertice) {
    color[vertice] = eVerticesDfsStatus::GRAY;
    startList.push_back(vertice); // i becomes gray, added to the start list
    const list<int>& adjVertice = originalGraph->GetAdjList(vertice);
    for (const int& adj : adjVertice)
    {
        if (color[adj] == eVerticesDfsStatus::WHITE)
        {
            //its a tree arc, adding to the dfs tree
            dfsGraph.AddEdge(vertice, adj);
            visit(adj);
        }
    }
    color[vertice] = eVerticesDfsStatus::BLACK;
    endList.push_back(vertice); // i becomes black, added to the end list
}
