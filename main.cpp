#include "graph.h"

void printGraph(Graph* g)
{
    for (int i = 0; i < g->getNumOfVertices(); i++)
    {
        cout << i + 1 << ": ";
        const list<int>& adj = g->getAdjList(i + 1);
        typename list<int>::const_iterator itr = adj.begin();
        for (int j = 0; j < adj.size(); j++)
        {
            cout << *itr << " ";
            ++itr;
        }
        cout << endl;
    }
}

int main() {
    Graph* g = new Graph(6);
    g->addEdge(1, 2);
    g->addEdge(1, 3);
    g->addEdge(3, 2);
    g->addEdge(2, 4);
    g->addEdge(5, 4);
    g->addEdge(5, 6);
    g->addEdge(6, 5);
    g->addEdge(4, 3);

    Graph* dfsGraph = g->runSharirKosaraju();

    printGraph(dfsGraph);
}