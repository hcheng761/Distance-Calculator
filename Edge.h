/*
	Howard Cheng
	CSCE 221 - 504
	Edge.h
*/

 // #pragma once 
#include "Vertex.h"

#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <vector>

using namespace std;


class Vertex;

class Edge {

private:
	Vertex *sVertP; // source vertex pointer
	Vertex *eVertP;  // end vertex pointer
	int weight; // edge weight 
	
public:
    
	Edge();
	Edge(Vertex* svert, Vertex* evert,int weit) {
		sVertP = svert;
		eVertP = evert;
		weight = weit;
	}
	int getWeight() {
		return weight;
	}
	Vertex* getsVertP() {
		return sVertP;
	}
	Vertex* geteVertP() {
		return eVertP;
	}
};

#endif