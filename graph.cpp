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

// setting the color list to be all white
void Graph::setColorList()
{
    colorList.resize(n + 1);
    for (eVerticesDfsStatus color : colorList)
    {
        color = eVerticesDfsStatus::WHITE;
    }
}

// setting the DFS object values
void Graph::setDFSObject(DFSObject* dfsObject)
{
    dfsObject->dfsGraph = new Graph(n);
    dfsObject->endList.reserve(n + 1);
    dfsObject->endList.push_back(0); // for ignoring index 0 later
}

// main loop of the DFS
Graph::DFSObject* Graph::runDFS(vector<int> startList)
{
    DFSObject* dfsObject = new DFSObject();
    setDFSObject(dfsObject);
    setColorList();
    for (int i = 1; i <= n; i++)
    {
        if (startList.size() != 0) // run DFS by given start list
        {
            if (colorList[startList[i]] == eVerticesDfsStatus::WHITE)
                visit(startList[i], dfsObject);
        }
        else // no given start list, run DFS from first vertice
        {
            if (colorList[i] == eVerticesDfsStatus::WHITE)
                visit(i, dfsObject);
        }
    }
    return dfsObject;
}

// visit recursive function
void Graph::visit(int vertice, DFSObject* dfsObject)
{
    colorList[vertice] = eVerticesDfsStatus::GRAY;
    Graph* dfsGraph = dfsObject->dfsGraph;
    const list<int>& adjVertice = getAdjList(vertice);
    for (const int& adj : adjVertice)
    {
        if (colorList[adj] == eVerticesDfsStatus::WHITE)
        {
            //its a tree arc, adding to the dfs tree
            dfsGraph->addEdge(vertice, adj);
            visit(adj, dfsObject);
        }
    }

    colorList[vertice] = eVerticesDfsStatus::BLACK;
    dfsObject->endList.push_back(vertice); // vertice becomes black, added to the end list
}

// Sharir-Kosaraju algorithm
Graph* Graph::runSharirKosaraju()
{
    DFSObject* dfsObject = new DFSObject();
    setDFSObject(dfsObject);

    // run DFS on the graph
    dfsObject = runDFS();

    // build the transposed graph
    Graph* transposedGraph = getTransposed();

    // Build reversed end list
    vector<int> reversedEndList = dfsObject->endList;
    reverse(reversedEndList.begin() + 1, reversedEndList.end());

    // run DFS on the transposed graph using the reversed end list
    DFSObject* transposedDfsGraph = transposedGraph->runDFS(reversedEndList);
    delete transposedGraph;

    return transposedDfsGraph->dfsGraph;
}