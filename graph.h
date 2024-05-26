#ifndef __GRAPH_H
#define __GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

class Graph
{
public:
	Graph(int n = 0);
	Graph(Graph& other);
	~Graph();

	int GetNumOfVertices() const { return n; }
	int GetNumOfEdges() const { return m; }

	static const string ERROR_MESSAGE;

	void MakeEmptyGraph(int n);
	void AddVertex();
	bool IsAdjacent(int u, int v) const;
	const list<int>& GetAdjList(int u) const;
	void AddEdge(int u, int v);
	void RemoveEdge(int u, int v);
	void PrintGraph() const { cout << n << " " << m << endl; }
	Graph* GetTransposed();

	struct DFSObject
	{
		Graph* dfsGraph;
		vector<int> endList;
		vector<int> dfsRoots;
		enum eVerticesDfsStatus { WHITE = 0, GRAY, BLACK };
		vector<eVerticesDfsStatus> colorList;
	};

	vector<int> GetDfsRoots();
	Graph* GetDfsGraph();

	void RunDFS();
	Graph* CreateSuperGraph();

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
	Graph* createSuperGraphWithDFS(vector<int> orderList);
	void visitSuperGraph(int vertex, int root, int superGraphMachingVertex, Graph* superGraph);

	void verifyVertexExists(int v) const;
	void verifySelfEdge(int u, int v) const;
	void verifyAmountOfVertices(int amountOfVertices) const;
	void throwErrorIfDfsObjectDoestExist() const;

};

#endif // !__GRAPH_H