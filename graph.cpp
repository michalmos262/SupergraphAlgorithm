#include "graph.h"

// Constructor
Graph::Graph(int n) {
    makeEmptyGraph(n);
}

// Method to create an empty graph with n vertices
void Graph::makeEmptyGraph(int n) {
    this->n = n;
    m = 0;
    adjacencyList.clear();
    adjacencyList.resize(n);
}

// Method to check if there is an edge between u and v
bool Graph::IsAdjacent(int u, int v) const {
    if (u > 0 && u <= n && v > 0 && v <= n) {
        const list<int>& neighbors = adjacencyList[u - 1];
        return find(neighbors.begin(), neighbors.end(), v) != neighbors.end();
    }
    return false;
}

// Method to get the adjacency list of vertex u
const list<int>& Graph::GetAdjList(int u) const {
    if (u > 0 && u <= n) {
        return adjacencyList[u - 1];
    }
    throw invalid_argument("Invalid vertex index");
}

// Method to add an edge
void Graph::AddEdge(int u, int v) {
    if (u > 0 && u <= n && v > 0 && v <= n && u != v) {
        if (!IsAdjacent(u, v)) {
            adjacencyList[u - 1].push_back(v);
            m++;
        }
    }
    else {
        throw invalid_argument("Invalid vertex index");
    }
}

// Method to remove an edge
void Graph::RemoveEdge(int u, int v) {
    if (u > 0 && u <= n && v > 0 && v <= n) {
        list<int>& uList = adjacencyList[u - 1];
        typename list<int>::const_iterator uIt = find(uList.begin(), uList.end(), v);
        if (uIt != uList.end()) {
            uList.erase(uIt);
            m--;
        }
        else {
            throw invalid_argument("Edge doesn't exist");
        }
    }
    else {
        throw invalid_argument("Invalid vertex index");
    }
        
}

// Method to get the transposed graph
Graph* Graph::getTransposed() const
{
    Graph* transposedGraph = new Graph(n);
    for (int v = 0; v < n; v++) {
        for (int u : adjacencyList[v]) {
            transposedGraph->adjacencyList[u - 1].push_back(v + 1);
        }
    }
    return transposedGraph;
}
