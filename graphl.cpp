//Graph L implementation file

//--------------------------------Graph L------------------

#include "graphl.h"

//----------------------------constructor-------------------------------------
GraphL::GraphL()
{
	size = 0;
	for (int i = 0; i < MAX_NODES; i++) {

		A[i].edgeHead = new EdgeNode;
		A[i].edgeHead->nextEdge = NULL;
        A[i].edgeHead->adjGraphNode = 0;
		A[i].visited = false;
	}
}

//------------------------destructor-------------------------------------
GraphL::~GraphL()
{
	for (int i = 0; i < MAX_NODES; i++) {
		EdgeNode* temp;
		while (A[i].edgeHead != NULL) {
			temp = A[i].edgeHead;
			A[i].edgeHead = A[i].edgeHead->nextEdge;
			delete temp;
		}
	}	
}

//---------------------buildGraph---------------------------------------------
void GraphL::buildGraph(ifstream& infile)
{
	//get number of nodes
	string s;
	getline(infile, s);
	istringstream iss(s);
	iss >> size;

	//set NodeData names
	for (int i = 1; i <= size; i++) {
		getline(infile, s);
		NodeData set(s);
		helper[i] = set;
		A[i].data = &helper[i];
	}

	//set node to node data into respective linked lists
	while (getline(infile, s)) {
		istringstream sstream(s);
		int start = -1;
		int end = -1;
		while (!sstream.eof()) {
			sstream >> start >> end;
		}
		if (start == 0) {
			break;
		}
		EdgeNode* incoming = new EdgeNode;
		incoming->adjGraphNode = end;
		incoming->nextEdge = A[start].edgeHead->nextEdge;
		A[start].edgeHead->nextEdge = incoming;
	}
}

//------------------------------------------------------displayGraph--------------------------------------
void GraphL::displayGraph()
{
	cout << "Graph:" << endl;
	for (int i = 1; i <= size; i++) {
		cout << "Node " << i << "        ";
		cout << *(A[i].data) << endl;
		EdgeNode* temp = A[i].edgeHead;
		while (temp->nextEdge != NULL) {
			cout << setw(7) << "edge " << i << " " << temp->nextEdge->adjGraphNode << endl;
			temp = temp->nextEdge;
		}
	}
	cout << endl;
}

//------------------------------------depthFirstSearch------------------------------------------------
void GraphL::depthFirstSearch()
{
	cout << "Depth-first ordering: ";
	for (int i = 1; i <= size; i++) {
		if (A[i].visited == false) {
			dfsHelper(i);
		}
	}
	cout << endl;
}

//-----------------------------------------dfsHelper---------------------------------------------
//helper method for depthFirstSearch
void GraphL::dfsHelper(int node)
{
	A[node].visited = true;
	cout << node << " ";
	while ((A[node].edgeHead->nextEdge != NULL)&& (A[(A[node].edgeHead->nextEdge->adjGraphNode)].visited == false)) {
			dfsHelper(A[node].edgeHead->nextEdge->adjGraphNode);
	}
}


