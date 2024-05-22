#include "graph.h"
#include "dfs.h"


//main for DFS check
int main() {
    Graph* g = new Graph(11);
    g->AddEdge(1, 2);
    g->AddEdge(1, 3);
    g->AddEdge(1, 5);
    g->AddEdge(2, 4);
    g->AddEdge(4, 3);
    g->AddEdge(5, 6);
    g->AddEdge(6, 7);
    g->AddEdge(6, 8);
    g->AddEdge(9, 8);
    g->AddEdge(9, 10);
    g->AddEdge(9, 11);
    g->AddEdge(11, 9);
    g->AddEdge(11, 10);
    Dfs d(g);

    vector<int> endList = d.getEndList();
    cout << "End list: ";
    for (vector<int>::iterator i = endList.begin(); i != endList.end(); ++i)
        cout << *i << " ";
    cout << endl;
    cout << "The dfs graph:" << endl;
    Graph* dfsGraph = d.getDfsGraph();
    for (int i = 0; i < dfsGraph->getNumOfVertices(); i++)
    {
        cout << i + 1 << ": ";
        const list<int>& adj = dfsGraph->GetAdjList(i + 1);
        typename list<int>::const_iterator itr = adj.begin();
        for (int j = 0; j < adj.size(); j++)
        {
            cout << *itr << " ";
            ++itr;
        }
        cout << endl;
    }
}

//int main() {
//    // Create a graph with 5 vertices
//    Graph g(5);
//
//    // Add some edges
//    g.AddEdge(1, 2);
//    g.AddEdge(1, 5);
//    g.AddEdge(1, 3);
//    g.AddEdge(2, 4);
//    g.AddEdge(2, 5);
//    g.AddEdge(3, 4);
//    g.AddEdge(4, 5);
//
//    // Print the graph
//    g.printGraph();
//
//    Graph* gTransposed = g.getTransposed();
//    
//    
//    for (int i = 0; i < g.getNumOfVertices(); i++)
//    {
//        cout << i + 1 << ": ";
//        const list<int>& adj = g.GetAdjList(i + 1);
//        typename list<int>::const_iterator itr = adj.begin();
//        for (int j = 0; j < adj.size(); j++)
//        {
//            cout << *itr << " ";
//            ++itr;
//        }
//        cout << endl;
//    }
//    cout << "-----------------------------------------------------" << endl;
//    for (int i = 0; i < gTransposed->getNumOfVertices(); i++)
//    {
//        cout << i + 1 << ": ";
//        const list<int>& adj = gTransposed->GetAdjList(i + 1);
//        typename list<int>::const_iterator itr = adj.begin();
//        for (int j = 0; j < adj.size(); j++)
//        {
//            cout << *itr << " ";
//            ++itr;
//        }
//        cout << endl;
//    }
//}
