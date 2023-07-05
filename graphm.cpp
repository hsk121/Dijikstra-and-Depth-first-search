//Graph M implementation file
#include "graphm.h"

//-------------------------------Graph M---------------------------------------------

//------------------------------Constructor---------------------------------------------
GraphM::GraphM()
{
	size = 0;
	for (int i = 0; i < MAXNODES; i++) {
		for (int j = 0; j < MAXNODES; j++) {
			C[i][j] = INT_MAX;
			T[i][j].dist = INT_MAX;
			T[i][j].visited = false;
			T[i][j].path = 0;
		}
	}
}

//----------------------------------buildGraph-----------------------------------------------
void GraphM::buildGraph(ifstream& infile)
{
    //getting number of nodes
	string s;
	getline(infile, s);
	istringstream iss(s);
    iss >> size;

    //setting data for graph nodes
    for (int i = 1; i <= size; i++) {
        data[i].setData(infile);
    }

    //setting adjacency matrix
    while (getline(infile, s)) {
        istringstream sstream(s);
        int start = -1;
        int end = -1;
        int weight = -1;
        while (!sstream.eof()) {
            sstream >> start >> end >> weight;
        }
        if (start == 0) {
            break;
        }
        C[start][end] = weight;
    }
}

//-------------------------------------insertEdge-------------------------------------
void GraphM::insertEdge(int from, int to, int weight)
{
    C[from][to] = weight;
}

//------------------------------------removeEdge-----------------------------------------
void GraphM::removeEdge(int from, int to)
{
    C[from][to] = INT_MAX;
}

//-----------------------------------findShortestPath-----------------------------------
void GraphM::findShortestPath()
{
    for (int source = 1; source <= size; source++) {
        T[source][source].dist = 0;
   
        for (int i = 1; i <= size; i++) {
            //finding minNode with smallest current distance at this point
            int minDist = INT_MAX;
            int minNode = 101;
            for (int i = 1; i <= size; i++) {
                if (T[source][i].dist < minDist && T[source][i].visited == false) {
                    minDist = T[source][i].dist;
                    minNode = i;
                }
            }
            //marking minNode as visited
            if (minDist != INT_MAX) {
                T[source][minNode].visited = true;

                //for each connectedNode adjacent minNode that is also not visited yet
                for (int connectedNode = 1; connectedNode <= size; connectedNode++) {
                    if (C[minNode][connectedNode] != INT_MAX && T[source][connectedNode].visited == false) {
                        if (T[source][minNode].dist + C[minNode][connectedNode] < T[source][connectedNode].dist) {
                            T[source][connectedNode].path = minNode;
                        }
                        T[source][connectedNode].dist = min(T[source][connectedNode].dist, T[source][minNode].dist + C[minNode][connectedNode]);
                    }
                }
            }
        }
    }

}

//---------------------------------------------displayAll-------------------------------------------------------------------
void GraphM::displayAll()
{
    cout << "Description" << setw(20) << "From Node" << "   "
        << "To Node" << "   " << "Dijkstra's   Path" << endl;
    for (int i = 1; i <= size; i++) {
        cout << data[i] << endl;
        for (int j = 1; j <= size; j++) {
            if (i != j) {
                cout << setw(27) << i << setw(13) << j << setw(9);
                if (T[i][j].dist == INT_MAX) {
                    cout << "---" << endl;
                }
                else {
                    cout << T[i][j].dist;
                    cout << setw(11) << i << " ";
             
                    displayPath(i, j, false);
                    cout << j << endl;
                }
            } 
        }
    }
}

//---------------------------------displayPath-------------------------------------------------------
//recursive helper method for path display
void GraphM::displayPath(int start, int end, bool name)
{
    int currentPath = T[start][end].path;
    if (currentPath != start) {
        displayPath(start, currentPath, name);
        if (name == false) {
            cout << currentPath << " ";
        }
        else {
            cout << data[currentPath] << endl;
        }
    }
}

//--------------------------------display-----------------------------------------------------------
void GraphM::display(int start, int end)
{
    cout << setw(4) << start << setw(9) << end << setw(9);
    if (T[start][end].dist == INT_MAX) {
        cout << "---" << endl;
    }
    else {
        cout << T[start][end].dist << setw(12);

        cout << start << " ";
        displayPath(start, end, false);
        cout << end << endl;

        cout << data[start] << endl;
        displayPath(start, end, true);
        cout << data[end] << endl;
    }
    cout << endl;
}



