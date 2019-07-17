// Yeseul An
// CSS343
// Prof: Min Chen
// Assignment3
// Program that implements dijkstra's shortest path algorithm for the given 
// input data and find the lowest cost paths for each node

//-------------------------------------------------------------------------------
// Dijkstra's shortest path algorithm: defined as an algorithm for finding 
// shortest path between nodes in a graph. It can be used for finding the shortest
// path from a single node to a single destination node by stopping the algorithm
// once the shortest path to the destination node has been determined.
//
// Implementation and assumptions:
//   -- Assumes that given input is properly formatted
//   -- Assumes that we would not given number of nodes more than 100
//   -- Included "limits.h" in order to define the infinite integer limit 
//--------------------------------------------------------------------------------

#pragma once
#include "nodedata.h"
#include <iostream>
#include <fstream>

const int MAX_NODES = 101;													// maximum number of nodes in the graph

class GraphM
{

public:
	GraphM();																// constructor
	void buildGraph(ifstream &infile);										// builds a graph with data
	bool insertEdge(const int from, const int to, const int dist);			// inserts a new edge to the graph
	bool removeEdge(const int from, const int to);							// removes the edge from the graph
	void findShortestPath();												// find shortest path for the graph
	void display(int from, int to);											// display shortest path between two nodes
	void displayAll();														// display shortest path for all nodes
	

private:
	struct TableType
	{
		bool visited;														// whether node has been visited
		int dist;															// shortest distance from source known so far
		int path;															// previous node in path of min dist
	};

	NodeData data[MAX_NODES];												// data for graph nodes
	int C[MAX_NODES][MAX_NODES];											// cost array, the adjacency matrix
	int size;																// number of nodes in the graph
	TableType T[MAX_NODES][MAX_NODES];										// stores visited, distance, path
	
	void findMinPath(int from, int to);										// helper for display methods for displaying path between from node and to node
	void findNode(int from, int to);										// helper for display methods for displaying nodes between from node and to node
	void initArray();														// initialize all array values as not visited
	int findNext(TableType temp[], int low, int high);						// find smallest next node v to be visited			
};
