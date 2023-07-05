//Graph M header file

//Assumptions and Implementation
//   -input is correct
//   -"0 0" signifies end of input
//--------------------------------Graph M------------------


#ifndef GRAPHM_H
#define GRAPHM_H
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

int const MAXNODES = 101;

class GraphM {
public:
	GraphM(); //constructor
	void buildGraph(ifstream&); //build graph using input
	void insertEdge(int, int, int); //insert edge into graph
	void removeEdge(int, int); //remove edge from graph
	void findShortestPath(); //using dijkstra's algorithm
	void displayAll(); //display all paths from all nodes
	void display(int, int); //display best path from two given nodes

private:
	struct TableType {
		bool visited;
		int dist;
		int path;
	};

	NodeData data[MAXNODES]; //node name data array
	int C[MAXNODES][MAXNODES]; //adjacency matrix
	int size; //number of nodes in graph
	TableType T[MAXNODES][MAXNODES]; //dijkstra calculations

	void displayPath(int, int, bool); //helper method for displaying paths
	
};

#endif

