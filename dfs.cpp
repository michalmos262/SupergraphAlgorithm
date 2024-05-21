#include "Dfs.h"

// Constructor - init the dfs
Dfs::Dfs(Graph* graph) {
    this->graph = graph;
    int n = graph->getNumOfVertices();
    this->color = (eVerticesDfsStatus*)calloc(n+1, sizeof(eVerticesDfsStatus));
    this->startList.resize(n);
    this->endList.resize(n);
    mainDfs();
}

// main loop of the dfs
void Dfs::mainDfs() {
    int n = graph->getNumOfVertices();
    for (int i = 1; i <= n; i++) {
        if (color[i] = eVerticesDfsStatus::WHITE)
            visit(i);
    }
}

// visit recursive function
void Dfs::visit(int vertice) {
    color[vertice] = eVerticesDfsStatus::GRAY;
    startList.push_back(vertice); // i becomes gray, added to the start list
    const list<int>& adjVertice = graph->GetAdjList(vertice);
    for (const int& adj : adjVertice)
    {
        //mark edge???
        visit(adj);
    }
    color[vertice] = eVerticesDfsStatus::BLACK;
    endList.push_back(vertice); // i becomes black, added to the end list
}
