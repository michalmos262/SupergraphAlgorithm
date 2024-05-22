#include "graph.h"

// Constructor
Graph::Graph(int n)
{
    makeEmptyGraph(n);
}

// copy constructor
Graph::Graph(Graph& other)
{
    n = other.n;
    m = other.m;
    makeEmptyGraph(n);
    for (int v = 1; v <= n; v++) {
        for (int u : other.adjacencyList[v]) {
            addEdge(v, u);
        }
    }
}

// Method to create an empty graph with n vertices
void Graph::makeEmptyGraph(int n) {
    this->n = n;
    m = 0;
    adjacencyList.clear();
    adjacencyList.resize(n + 1);
}

// Method to check if there is an edge between u and v
bool Graph::isAdjacent(int u, int v) const {
    if (u > 0 && u <= n && v > 0 && v <= n) {
        const list<int>& neighbors = adjacencyList[u];
        return find(neighbors.begin(), neighbors.end(), v) != neighbors.end();
    }
    return false;
}

// Method to get the adjacency list of vertex u
const list<int>& Graph::getAdjList(int u) const {
    if (u > 0 && u <= n) {
        return adjacencyList[u];
    }
    throw invalid_argument("Invalid vertex index");
}

// Method to add an edge
void Graph::addEdge(int u, int v) {
    if (u > 0 && u <= n && v > 0 && v <= n && u != v) {
        if (!isAdjacent(u, v)) {
            adjacencyList[u].push_back(v);
            m++;
        }
    }
    else {
        throw invalid_argument("Invalid vertex index");
    }
}

// Method to remove an edge
void Graph::removeEdge(int u, int v) {
    if (u > 0 && u <= n && v > 0 && v <= n) {
        list<int>& uList = adjacencyList[u];
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
Graph* Graph::getTransposed()
{
    Graph* transposedGraph = new Graph(n);
    for (int v = 1; v <= n; v++) {
        for (int u : adjacencyList[v]) {
            transposedGraph->addEdge(u, v);
        }
    }
    return transposedGraph;
}