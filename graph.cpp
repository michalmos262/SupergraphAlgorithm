#include "graph.h"

// Constructor
Graph::Graph(int n)
{
    MakeEmptyGraph(n);
}

// Copy constructor
Graph::Graph(Graph& other)
{
    n = other.n;
    m = other.m;
    MakeEmptyGraph(n);
    for (int v = 1; v <= n; v++) {
        for (int u : other.adjacencyList[v]) {
            AddEdge(v, u);
        }
    }
}

// Dtor
Graph::~Graph()
{
    if (!dfsObject)
        delete dfsObject;
}


// Method to create an empty graph with n vertices
void Graph::MakeEmptyGraph(int n)
{
    this->n = n;
    m = 0;
    adjacencyList.clear();
    adjacencyList.resize(n + 1);
}

// Method to add a vertex to the graph
void Graph::AddVertex()
{
    n += 1;
    adjacencyList.resize(n + 1);
}


// Method to check if there is an edge between u and v
bool Graph::IsAdjacent(int u, int v) const
{
    if (u > 0 && u <= n && v > 0 && v <= n) {
        const list<int>& neighbors = adjacencyList[u];
        return find(neighbors.begin(), neighbors.end(), v) != neighbors.end();
    }
    return false;
}

// Method to get the adjacency list of vertex u
const list<int>& Graph::GetAdjList(int u) const
{
    if (u > 0 && u <= n) {
        return adjacencyList[u];
    }
    throw invalid_argument("Invalid vertex index");
}

// Method to add an edge
void Graph::AddEdge(int u, int v)
{
    if (u > 0 && u <= n && v > 0 && v <= n && u != v) {
        if (!IsAdjacent(u, v)) {
            adjacencyList[u].push_back(v);
            m++;
        }
    }
    else {
        throw invalid_argument("Invalid vertex index");
    }
}

// Method to remove an edge
void Graph::RemoveEdge(int u, int v)
{
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
Graph* Graph::GetTransposed()
{
    Graph* transposedGraph = new Graph(n);
    for (int v = 1; v <= n; v++) {
        for (int u : adjacencyList[v]) {
            transposedGraph->AddEdge(u, v);
        }
    }
    return transposedGraph;
}

// Setting the DFS object values
void Graph::setDFSObject()
{
    this->dfsObject = new DFSObject();
    dfsObject->dfsGraph = new Graph(n);
    dfsObject->endList.reserve(n + 1);
    dfsObject->endList.push_back(0); // for ignoring index 0 later
    dfsObject->dfsRoots.resize(n + 1);
    machingVetexInSuperGraph.resize(n + 1);
    setColorList();
}

// Call an error if requested a DFS object bedore creating one
void Graph::throwErrorIfDfsObjectDoestExist()
{
    if (dfsObject == nullptr)
        throw logic_error("please call runDFS or runSharirKosaraju first.");
}

// Method to return the DFS roots
vector<int> Graph::GetDfsRoots()
{
    throwErrorIfDfsObjectDoestExist();
    return dfsObject->dfsRoots;
}

// Methos to return the DFS graph
Graph* Graph::GetDfsGraph()
{
    throwErrorIfDfsObjectDoestExist();
    return dfsObject->dfsGraph;
}

// Setting the color list to be all white
void Graph::setColorList()
{
    dfsObject->colorList.resize(n + 1);
    for (DFSObject::eVerticesDfsStatus color : dfsObject->colorList)
    {
        color = DFSObject::eVerticesDfsStatus::WHITE;
    }
}

// Main loop of the DFS
void Graph::RunDFS()
{
    setDFSObject();

    for (int i = 1; i <= n; i++)
    {
        if (dfsObject->colorList[i] == DFSObject::eVerticesDfsStatus::WHITE)
            visit(i, i);
    }
}

// Visit recursive function, create the DFS tree
void Graph::visit(int vertex, int root)
{
    dfsObject->dfsRoots[vertex] = root;
    dfsObject->colorList[vertex] = DFSObject::eVerticesDfsStatus::GRAY;
    const list<int>& adjVertices = GetAdjList(vertex);
    for (const int& adj : adjVertices)
    {
        if (dfsObject->colorList[adj] == DFSObject::eVerticesDfsStatus::WHITE)
        {
            //its a tree arc, adding to the dfs tree
            dfsObject->dfsGraph->AddEdge(vertex, adj);
            visit(adj, root);
        }
    }
    dfsObject->colorList[vertex] = DFSObject::eVerticesDfsStatus::BLACK;
    dfsObject->endList.push_back(vertex); // vertex becomes black, added to the end list
}

// Run the DFS algoritm on the transpose graph and create the Super Graph
// does not create the DFS graph or the end list of the origin graph!
Graph* Graph::createSuperGraphWithDFS(vector<int> orderList)
{
    setDFSObject();
    int superGraphSize = 0;
    Graph* superGraph = new Graph(0);

    for (int i = 1; i <= n; i++)
    {
        if (dfsObject->colorList[orderList[i]] == DFSObject::eVerticesDfsStatus::WHITE)
        {
            superGraph->AddVertex();
            superGraphSize += 1;
            visitSuperGraph(orderList[i], orderList[i], superGraphSize, superGraph);
        }
    }

    return superGraph;
}

// Add the edeges to the Super Graph with the visit ajusted algoritm
void Graph::visitSuperGraph(int vertex, int root,
    int superGraphMachingVertex, Graph* superGraph)
{
    machingVetexInSuperGraph[vertex] = superGraphMachingVertex;
    dfsObject->colorList[vertex] = DFSObject::eVerticesDfsStatus::GRAY;
    const list<int>& adjVertices = GetAdjList(vertex);
    for (const int& adj : adjVertices)
    {
        if (dfsObject->colorList[adj] == DFSObject::eVerticesDfsStatus::WHITE)
        {
            visitSuperGraph(adj, root, superGraphMachingVertex, superGraph);
        }
        else if (dfsObject->colorList[adj] == DFSObject::eVerticesDfsStatus::BLACK &&
            machingVetexInSuperGraph[vertex] != machingVetexInSuperGraph[adj])
        {
            //if its a back arc and the vertices doest have the same root
            //add the transpose edge to the superGraph
            superGraph->AddEdge(machingVetexInSuperGraph[adj], machingVetexInSuperGraph[vertex]);
        }
    }
    dfsObject->colorList[vertex] = DFSObject::eVerticesDfsStatus::BLACK;
}

// Create Super Graph with - Sharir-Kosaraju algorithm
Graph* Graph::CreateSuperGraph()
{
    // run DFS on the graph
    RunDFS();

    // build the transposed graph
    Graph* transposedGraph = GetTransposed();

    // Build reversed end list
    vector<int> reversedEndList = dfsObject->endList;
    reverse(reversedEndList.begin() + 1, reversedEndList.end());

    // run DFS on the transposed graph using the reversed end list
    Graph* superGraph = transposedGraph->createSuperGraphWithDFS(reversedEndList);
    
    //for us for debug!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for (int i = 1; i <= transposedGraph->GetNumOfVertices(); i++)
    {
        cout << "vertex " << i << " vertex in super graph " << transposedGraph->machingVetexInSuperGraph[i] << endl;
    }
    
    delete transposedGraph;

    return superGraph;
}