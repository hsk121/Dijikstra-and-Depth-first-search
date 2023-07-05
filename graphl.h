//Graph L header file

//Assumptions and Implementation
//   -input is correct
//   -"0 0" signifies end of input
//--------------------------------Graph L------------------

#ifndef GRAPHL_H
#define GRAPHL_H
#include <string>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <climits>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "nodedata.h"
using namespace std;

int const MAX_NODES = 101;

class GraphL {

public:
	GraphL();  //construcotr
	~GraphL();  //destructor
	void buildGraph(ifstream&);  //builds graph using input
	void displayGraph();  //displays all possible node to node paths
	void depthFirstSearch();  //calculates and displays depth first order path

private:
	struct EdgeNode;
	struct GraphNode {
		EdgeNode* edgeHead;
		NodeData* data;
		bool visited;
	};
	struct EdgeNode {
		int adjGraphNode;
		EdgeNode* nextEdge;
	};
	
	GraphNode A[MAX_NODES]; //holds node to node path info
	NodeData helper[MAX_NODES]; //helper array for node data
	int size; //number of nodes in graph
	void dfsHelper(int); //helper method for depthFirstSearch method

};

#endif
