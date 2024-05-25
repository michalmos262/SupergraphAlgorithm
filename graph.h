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

	void MakeEmptyGraph(int n);
	void addVertex();
	bool IsAdjacent(int u, int v) const;
	const list<int>& GetAdjList(int u) const;
	void AddEdge(int u, int v);
	void RemoveEdge(int u, int v);
	void printGraph() const { cout << n << " " << m << endl; }
	Graph* getTransposed();

	struct DFSObject
	{
		Graph* dfsGraph;
		vector<int> endList;
		vector<int> dfsRoots;
		enum eVerticesDfsStatus { WHITE = 0, GRAY, BLACK };
		vector<eVerticesDfsStatus> colorList;
	};

	vector<int> getDfsRoots();
	Graph* getDfsGraph();

	void runDFS();
	Graph* createSuperGraph();

private:
	int n; // number of vertices
	int m; // number of edges
	vector<list<int>> adjacencyList;
	DFSObject* dfsObject = nullptr;
	vector<int> machingVetexInSuperGraph;

	void setDFSObject();
	void setColorList();
	void visit(int vertex, int root);
	//below method is private, use only on the transpose graph
	Graph* runDFSCreatingSuperGraph(vector<int> orderList);
	void visitSuperGraph(int vertex, int root, int superGraphMachingVertex, Graph* superGraph);
	void throwErrorIfDfsObjectDoestExist();

};

#endif // !__GRAPH_H