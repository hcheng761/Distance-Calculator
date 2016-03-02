/*
	Howard Cheng
	CSCE 221 - 504
	Vertex.h
*/

#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Edge.h"
 
using namespace std;

class Graph;
class Edge;

class Vertex {

private:
	vector<Edge*> inList; // source vertex
    vector<Edge*> outList; // end vertex 
	int id;
	friend class Graph;
public:

	Vertex(int sid) {
		id = sid;
	}
	int getID() const {
		return id;
	}
	vector<Edge*> getOutEdges() const {
		return outList;
	}
	vector<Edge*> getInEdges() const {
		return inList;
	}
};

#endif