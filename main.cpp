#include "graph.h"


int main() {
    // Create a graph with 5 vertices
    Graph g(5);

    // Add some edges
    g.AddEdge(1, 2);
    g.AddEdge(1, 5);
    g.AddEdge(1, 3);
    g.AddEdge(2, 4);
    g.AddEdge(2, 5);
    g.AddEdge(3, 4);
    g.AddEdge(4, 5);

    // Print the graph
    g.printGraph();

    Graph* gTransposed = g.getTransposed();
    
    
    for (int i = 0; i < g.getNumOfVertices(); i++)
    {
        cout << i + 1 << ": ";
        const list<int>& adj = g.GetAdjList(i + 1);
        typename list<int>::const_iterator itr = adj.begin();
        for (int j = 0; j < adj.size(); j++)
        {
            cout << *itr << " ";
            ++itr;
        }
        cout << endl;
    }
    cout << "-----------------------------------------------------" << endl;
    for (int i = 0; i < gTransposed->getNumOfVertices(); i++)
    {
        cout << i + 1 << ": ";
        const list<int>& adj = gTransposed->GetAdjList(i + 1);
        typename list<int>::const_iterator itr = adj.begin();
        for (int j = 0; j < adj.size(); j++)
        {
            cout << *itr << " ";
            ++itr;
        }
        cout << endl;
    }
}