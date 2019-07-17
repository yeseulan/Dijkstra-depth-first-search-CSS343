// Yeseul An
// CSS343
// Prof: Min Chen
// Assignment3
// Program that implements depth-first search algorithm and display the graph 
// information based on the search 

#include "graphl.h"
#include "limits.h"
#include "iomanip"

//----------------------------------------------------------------------------
// constructor
// Constructs an empty graph that is used for depth-first search
GraphL::GraphL()
{
	this->size = 0;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		nodeArray[i].edgeHead = NULL;
		nodeArray[i].data = NULL;
		nodeArray[i].visited = false;
	}
}

//----------------------------------------------------------------------------
// destructor
// Destroys the graph and deletes the data it holds
GraphL::~GraphL()
{
	destroyHelper();
}

//----------------------------------------------------------------------------
// destroyHelper
// Helper function to destroy and deletes the data in the graph 
// Data is deleted in the graph
void GraphL::destroyHelper()
{
	for (int i = 1; i <= size; i++)
	{
		nodeArray[i].visited = false;
		if (nodeArray[i].data != NULL)
		{
			delete nodeArray[i].data;
			nodeArray[i].data = NULL;
		}
		if (nodeArray[i].edgeHead != NULL)
		{
			EdgeNode *tmp = nodeArray[i].edgeHead;
			while (tmp != NULL)
			{
				nodeArray[i].edgeHead = nodeArray[i].edgeHead->nextEdge;
				delete tmp;
				tmp = NULL;
				tmp = nodeArray[i].edgeHead;
			}
		}
	}
}

//----------------------------------------------------------------------------
// buildGraph
// Parameters infile is given input data
// Builds the graph based on the data given in the file
void GraphL::buildGraph(ifstream &infile)
{
	infile >> this->size;
	string name = "";
	getline(infile, name);

	for (int i = 1; i <= size; i++)
	{
		getline(infile, name);
		NodeData *tmp = new NodeData(name);
		nodeArray[i].data = tmp;
		tmp = NULL;
	}

	int from, to;
	while (infile >> from >> to)
	{
		if (from == 0)
		{
			break;
		}

		EdgeNode *newData = new EdgeNode;
		newData->adjGraphNode = to;
		newData->nextEdge = NULL;
		if (nodeArray[from].edgeHead == NULL)
		{
			nodeArray[from].edgeHead = newData;
		}
		else
		{
			newData->nextEdge = nodeArray[from].edgeHead;
			nodeArray[from].edgeHead = newData;
		}
		newData = NULL;
	}
}

//----------------------------------------------------------------------------
// displayGraph
// Displays each node information and edge in the graph
// Information of the graph is displayed
void GraphL::displayGraph()
{
	cout << "Graph:" << endl;
	for (int i = 1; i <= this->size; i++)
	{
		cout << "Node " << i << "                " << *nodeArray[i].data << endl;
		EdgeNode *tmp = nodeArray[i].edgeHead;
		while (tmp != NULL)
		{
			cout << "   " << "edge " << i << " " << tmp->adjGraphNode << " " << endl;
			tmp = tmp->nextEdge;
		}
		delete tmp;
		tmp = NULL;
	}
	cout << endl;
}

//----------------------------------------------------------------------------
// depthFristSearch
// Does a depth-first search and displays each node in depth-first order 
// Each node is displayed in depth-first order
void GraphL::depthFirstSearch()
{
	cout << "Depth-first ordering: ";
	for (int i = 1; i <= this->size; i++)
	{
		if (!this->nodeArray[i].visited)
		{
			depthFirstSearchHelper(i);
		}
	}
	cout << endl;
}

//----------------------------------------------------------------------------
// depthFristSearchHelper
// Helps depthFirstSearch method to do a depth-first search and displays 
// each node in depth-first order 
// Each node is displayed in depth-first order
void GraphL::depthFirstSearchHelper(int vertex)
{
	cout << vertex << " ";
	nodeArray[vertex].visited = true;
	EdgeNode *cur = nodeArray[vertex].edgeHead;

	while (cur != NULL)
	{
		if (!nodeArray[cur->adjGraphNode].visited)
		{
			depthFirstSearchHelper(cur->adjGraphNode);
		}
		else
		{
			cur = cur->nextEdge;
		}
	}
}