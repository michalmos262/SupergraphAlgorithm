#ifndef __DFS_
#define __DFS_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "graph.h"

using namespace std;

class Dfs {
public:
	enum eVerticesDfsStatus { WHITE, GRAY, BLACK };
	Dfs(Graph* graph);
	list<int> getStartList() { return startList; }
	list<int> getEndList() { return endList; }

private:
	Graph* graph;
	eVerticesDfsStatus* color;
	Graph* dfsTrees;
	list<int> startList, endList;
	void mainDfs();
	void visit(int vertices);

};

#endif // !__DFS_
