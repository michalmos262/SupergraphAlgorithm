#ifndef __DFS_RUNNER_H
#define __DFS_RUNNER_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "graph.h"

using namespace std;

class DFSRunner {
public:
	enum eVerticesDfsStatus { WHITE = 0, GRAY, BLACK };

	DFSRunner(Graph* graph);
	~DFSRunner();

	vector<int> getEndList() { return endList; }
	Graph* getDfsGraph() { return dfsGraph; }

	void runDFS(vector<int> startList = {});
	void runSharirKosaraju();
	void runCCDFS();

private:
	Graph* originalGraph;
	vector<eVerticesDfsStatus> colorList;
	Graph* dfsGraph;
	vector<int> endList;
	
	void visit(int vertices);
	void CCvisit(int vertice, int currentRoot);
};

#endif // !__DFS_H
