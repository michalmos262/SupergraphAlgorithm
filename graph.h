#ifndef __GRAPH_H
#define __GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Graph
{
private:
	int n; // number of vertices
	int m; // number of edges
	vector<list<int>> adjacencyList;  // adjacency list representation

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
};

#endif // !__GRAPH_H