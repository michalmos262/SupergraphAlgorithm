#ifndef __GRAPH_H
#define __GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Graph
{
public:
	Graph(int n = 0);
	Graph(Graph& other);

	int getNumOfVertices() const { return n; }
	int getNumOfEdges() const { return m; }
	void makeEmptyGraph(int n);
	bool isAdjacent(int u, int v) const;
	const list<int>& getAdjList(int u) const;
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	void printGraph() const { cout << n << " " << m << endl; }
	Graph* getTransposed();

	struct DFSObject
	{
		Graph* dfsGraph;
		vector<int> endList;
	};
	DFSObject* runDFS(vector<int> startList = {});
	Graph* runSharirKosaraju();

private:
	int n; // number of vertices
	int m; // number of edges
	vector<list<int>> adjacencyList;

	enum eVerticesDfsStatus { WHITE = 0, GRAY, BLACK };
	vector<eVerticesDfsStatus> colorList;

	void setDFSObject(DFSObject* dfsObject);
	void setColorList();
	void visit(int vertice, DFSObject* dfsObject);
};

#endif // !__GRAPH_H