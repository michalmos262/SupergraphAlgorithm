#ifndef __DFS_H
#define __DFS_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "graph.h"

using namespace std;

class Dfs {
public:
	enum eVerticesDfsStatus { WHITE = 0, GRAY, BLACK };
	Dfs(Graph* graph);
	~Dfs();
	vector<int> getStartList() { return startList; }
	vector<int> getEndList() { return endList; }
	Graph* getDfsGraph() { return dfsGraph; }

private:
	Graph* originalGraph;
	eVerticesDfsStatus* color;
	Graph* dfsGraph;
	vector<int> startList, endList;
	void mainDfs();
	void visit(int vertices);

};

#endif // !__DFS_H
