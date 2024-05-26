#include "graph.h"

void AddEdgesToGraph(Graph& graph, int numOfEdges);

/// <summary>
/// The program recieves a number of vertices and a number of edges and creates a graph from them.
/// Then, the program creates the supergraph of the graph.
/// </summary>
/// <returns>The number of vertices and edges of the Supergraph</returns>
int main() {
    int numOfVertices, numOfEdges;

    try
    {
        cin >> numOfVertices;
        Graph graph(numOfVertices);

        cin >> numOfEdges;
        AddEdgesToGraph(graph, numOfEdges);

        Graph* superGraph = graph.CreateSuperGraph();
        cout << superGraph->GetNumOfVertices() << " " << superGraph->GetNumOfEdges();

        delete superGraph;
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
        exit(1);
    }
}

// Add edges to graph
void AddEdgesToGraph(Graph& graph, int numOfEdges)
{
    int u, v;
    if (numOfEdges < 0)
    {
        throw invalid_argument(Graph::ERROR_MESSAGE);
    }
    for (int i = 0; i < numOfEdges; i++)
    {
        cin >> u >> v;
        graph.AddEdge(v, u);
    }
}