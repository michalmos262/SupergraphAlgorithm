#include "graph.h"

void printGraph(Graph* g)
{
    for (int i = 0; i < g->getNumOfVertices(); i++)
    {
        cout << i + 1 << ": ";
        const list<int>& adj = g->GetAdjList(i + 1);
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
    Graph* g = new Graph(11);
    g->AddEdge(1, 2);
    g->AddEdge(1, 3);
    g->AddEdge(1, 5);
    g->AddEdge(2, 4);
    g->AddEdge(3, 2);
    g->AddEdge(4, 3);
    g->AddEdge(5, 6);
    g->AddEdge(6, 7);
    g->AddEdge(6, 8);
    g->AddEdge(8, 5);
    g->AddEdge(9, 8);
    g->AddEdge(9, 10);
    g->AddEdge(9, 11);
    g->AddEdge(11, 9);
    g->AddEdge(11, 10);

    Graph* superGraph = g->createSuperGraph();
    printGraph(superGraph);
}