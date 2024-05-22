#include "dfsRunner.h"

// Constructor - init the DFS alrogirthms
DFSRunner::DFSRunner(Graph* graph) {
    originalGraph = graph;
    int n = graph->getNumOfVertices();
    colorList.resize(n + 1);
    for (eVerticesDfsStatus color : colorList)
    {
        color = eVerticesDfsStatus::WHITE;
    }
    endList.reserve(n + 1);
    endList.push_back(0); // for ignoring index 0 later
    dfsGraph = new Graph(n);
}

 // Dtor - delete the dfs graph
DFSRunner::~DFSRunner() {
    delete dfsGraph;
}

// main loop of the dfs
void DFSRunner::runDFS(vector<int> startList) {
    int n = originalGraph->getNumOfVertices();
    for (int i = 1; i <= n; i++)
    {
        if (startList.size() != 0) // run DFS by given start list
        {
            if (colorList[startList[i]] == eVerticesDfsStatus::WHITE)
                visit(startList[i]);
        }
        else // no given start list, run DFS from first vertice
        {
            if (colorList[i] == eVerticesDfsStatus::WHITE)
                visit(i);
        }
    }
}

// visit recursive function
void DFSRunner::visit(int vertice)
{
    colorList[vertice] = eVerticesDfsStatus::GRAY;
    const list<int>& adjVertice = originalGraph->getAdjList(vertice);
    for (const int& adj : adjVertice)
    {
        if (colorList[adj] == eVerticesDfsStatus::WHITE)
        {
            //its a tree arc, adding to the dfs tree
            dfsGraph->addEdge(vertice, adj);
            visit(adj);
        }
    }
    colorList[vertice] = eVerticesDfsStatus::BLACK;
    endList.push_back(vertice); // vertice becomes black, added to the end list
}

void DFSRunner::runSharirKosaraju()
{
    // run DFS on the graph
    runDFS();

    // build the transposed graph
    Graph* transposedGraph = originalGraph->getTransposed();

    // Build reversed end list
    vector<int> reversedEndList = endList;
    reverse(reversedEndList.begin()+1, reversedEndList.end());
    // run DFS on the transposed graph using the revered end list
    DFSRunner transposedGraphRunner(transposedGraph);
    transposedGraphRunner.runDFS(reversedEndList);

    delete dfsGraph;
    dfsGraph = new Graph(*transposedGraphRunner.getDfsGraph());
    endList = transposedGraphRunner.getEndList();
    delete transposedGraph;
}