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
	int getNumOfVertices() const { return n; }
	int getNumOfEdges() const { return m; }
	void makeEmptyGraph(int n);
	bool IsAdjacent(int u, int v) const;
	const list<int>& GetAdjList(int u) const;
	void AddEdge(int u, int v);
	void RemoveEdge(int u, int v);
	void printGraph() const { cout << n << " " << m << endl; }
};

#endif // !__GRAPH_H
