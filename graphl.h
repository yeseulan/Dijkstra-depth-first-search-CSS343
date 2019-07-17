// Yeseul An
// CSS343
// Prof: Min Chen
// Assignment3
// Program that implements depth-first algorithm and display the graph 
// information based on the algorithm 

//-------------------------------------------------------------------------------
// Depth-first algorithm: defined as an algorithm for traversing or searching
// tree or graph data structures following depth-first search. For example, one starts
// at the source and explores as far as possible along each linked edges.
//
// Implementation and assumptions:
//   -- Assumes that given input is properly formatted
//   -- Assumes that we would not given number of nodes more than 100 elements
//   -- GraphNode and EdgeNode structs are used to represent graph nodes of a graph
//   and its edges
//--------------------------------------------------------------------------------

#pragma once
#include "nodedata.h"
#include <iostream>
#include <fstream>

using namespace std;

const int ARRAY_SIZE = 101;

class GraphL
{

public:
	GraphL();									// constructor
	~GraphL();									// destructor
	void buildGraph(ifstream &infile);			// builds a graph with data
	void displayGraph();						// display graph with depth-first algorithm
	void depthFirstSearch();					// does depth-first algorithm

private:
	struct EdgeNode;							// forward reference for the compiler

	struct GraphNode							// Nodes in a graph that contains data for a graph node
	{
		EdgeNode *edgeHead;						// head of the list of edges
		NodeData *data;							// data information about each node
		bool visited;							// data information about whether a node is visited or not 
	};

	struct EdgeNode
	{
		int adjGraphNode;						// subscript of the adjacent graph node
		EdgeNode *nextEdge;						// pointer points to the next EdgeNode
	};

	void destroyHelper();						// helper method to destroy the graph 
	void depthFirstSearchHelper(int vertex);	// helper method for the depthFristSearch method

	GraphNode nodeArray[ARRAY_SIZE];			// array to store the nodes of a graph
	int size;									// number of nodes in a graph
};

