// Yeseul An
// CSS343
// Prof: Min Chen
// Assignment3
// Program that implements dijkstra's shortest path algorithm for the given 
// input data and find the lowest cost paths for each node

#include "graphm.h"
#include "limits.h"
#include <iomanip>

//----------------------------------------------------------------------------
// constructor
// Constructs an empty graph that is used for dijkstra's shortest path algorithm
GraphM::GraphM()
{
	this->size = 0;
	for (int i = 1; i < MAX_NODES; i++)
	{
		for (int j = 1; j < MAX_NODES; j++)
		{
			C[i][j] = INT_MAX;
			T[i][j].visited = false;
			T[i][j].dist = INT_MAX;
			T[i][j].path = 0;
		}
	}
}

//----------------------------------------------------------------------------
// buildGraph
// Parameter infile is given input data 
// Builds the graph based on the data given in the file
void GraphM::buildGraph(ifstream &infile)
{
	infile >> this->size;
	string dummy = "";
	getline(infile, dummy);

	for (int i = 1; i <= size; i++)
	{
		data[i].setData(infile);
	}

	int from, to, cost;
	while (infile >> from >> to >> cost)
	{
		if (from == 0)
		{
			break;
		}
		C[from][to] = cost;
	}
}

//----------------------------------------------------------------------------
// insertEdge
// Parameter from is a source node, to is a destination node, and cost is the 
// weight between nodes
// The edge is inserted between from and to node with given cost
bool GraphM::insertEdge(int from, int to, int cost)
{
	if (from > this->size || from < 1 || to > this->size || to < 1)			// check to see whether nodes are out of boundary
	{
		return false;
	}

	else if (from == to && cost != 0)										// check to see whether from node == to node and has non-zero cost 

	{
		return false;
	}

	else if (cost < 0)														// check to see cost is negative
	{
		return false;
	}

	else
	{																		// adds a new edge to the graph
		this->C[from][to] = cost;
		return true;
	}
}

//----------------------------------------------------------------------------
// removeEdge
// Parameter from is a source node and to is a destination nodes
// The edge between existing nodes from and to is removed
bool GraphM::removeEdge(const int from, const int to)
{
	if (from > size || from < 1 || to > size || to < 1)						// checks to see from node is in the boundary
	{
		return false;
	}
	else if (C[from][to] == INT_MAX)										// if there is no existing edge between from node and to node
	{
		return false;
	}
	else
	{
		C[from][to] = INT_MAX;												// deletes the existing edge from the graph
		return true;
	}
}

//----------------------------------------------------------------------------
// findShortestPath
// Finds a shortest paths of nodes in a graph using dijkstra's algorithm
// The shortest paths between nodes are all found and information is saved
void GraphM::findShortestPath()
{
	int v = 0;
	int w = 0;
	int count = 1;

	for (int source = 1; source <= size; source++)
	{
		T[source][source].dist = 0;

		while (count != size)
		{
			v = findNext(T[source], 1, size);
			T[source][v].visited = true;

			for (int i = 1; i <= size; i++)
			{
				w = i;

				if (!T[source][w].visited && C[v][w] != INT_MAX)
				{
					if (!(T[source][w].dist < T[source][v].dist + C[v][w]))
					{
						T[source][w].dist = T[source][v].dist + C[v][w];
						T[source][w].path = v;
					}
				}
			}
			count++;
		}
		count = 1;
		initArray();
	}
}

//----------------------------------------------------------------------------
// findNext
// Paratemters temp is an array that contains current distance, low and high
// are values in the array
int GraphM::findNext(TableType temp[], int low, int high)
{
	int nextNode = 1;
	int min = INT_MAX;

	for (int i = 1; i <= size; i++)
	{
		if (temp[i].dist < min && temp[i].visited == false)
		{
			nextNode = i;
			min = temp[i].dist;
		}
	}
	return nextNode;
}

//----------------------------------------------------------------------------
// initArray
// Initializes the array values as not visited
void GraphM::initArray()
{
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++)
		{
			T[i][j].visited = false;
		}
	}
}

//----------------------------------------------------------------------------
// display
// Parameter from is the source node and to is the destination node
// Displays shortest path and node information between the source and 
// the destination node
void GraphM::display(int from, int to)
{
	if ((from > size || from < 1) || (to > size || to < 1))					// if node from and to are out of boundary
	{
		cout << setw(7) << from << setw(9) << to;
		cout << setw(11) << "----" << endl;
	}

	else if (T[from][to].dist != INT_MAX)
	{
		cout << setw(7) << from << setw(9) << to;
		cout << setw(11) << T[from][to].dist << setw(15);

		findMinPath(from, to);
		cout << endl;
		findNode(from, to);
	}

	else
	{
		cout << setw(7) << from << setw(9) << to;							// handles case when from == to
		cout << setw(11) << "----" << endl;
	}
	cout << endl;
}

//----------------------------------------------------------------------------
// displayAll
// Displays the shortest path information of all nodes in the graph
void GraphM::displayAll()
{
	cout << "Description" << setw(20) << "From Node" << setw(12) << "To Node";
	cout << setw(14) << "Dijkstra's" << setw(8) << "Path" << endl;

	for (int i = 1; i <= size; i++)
	{
		cout << this->data[i] << endl;
		for (int j = 1; j <= size; j++)
		{
			if (T[i][j].dist > 0 && T[i][j].dist < INT_MAX)
			{
				cout << setw(27) << i << setw(12) << j;
				cout << setw(12) << T[i][j].dist << setw(10);
				findMinPath(i, j);
				cout << endl;
			}
			else
			{
				if (i != j)
				{
					cout << setw(27) << i << setw(12) << j;
					cout << setw(12) << "----" << endl;
				}
			}
		}
	}
}
	

//----------------------------------------------------------------------------
// findMinPath
// Helper function for display functions which is used to display the shortest path 
// Finds and displays the shortest path information between the source node 
// and destination node
void GraphM::findMinPath(int from, int to)
{
	if (T[from][to].dist == INT_MAX)
	{
		return;
	}

	if (from == to)
	{
		cout << to << " ";
		return;
	}

	int path = to;
	findMinPath(from, T[from][to].path);
	cout << path << " ";
}

//----------------------------------------------------------------------------
// findNode
// Helper function for display functions which is used to display the nodes 
// in the shortest path
// Finds and displays the node information between the source node 
// and destination node
void GraphM::findNode(int from, int to)
{
	if (T[from][to].dist == INT_MAX)
	{
		return;
	}
	if (from == to)
	{
		cout << data[from] << endl;
		return;
	}
	else
	{
		int node = to;
		findNode(from, T[from][to].path);
		cout << data[node] << endl;
	}
}