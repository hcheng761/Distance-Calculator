/*
	Howard Cheng
	CSCE 221 - 504
	Graph.h
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Vertex.h"
#include "Edge.h"

using namespace std;

class Edge;
class Vertex;

class Graph{

private:
	vector<Vertex*> vertList;
	vector<Edge*> edgeList;
	string fileout;
public:
	Graph(string filename) {
    //
    //  The vertex with ID x is stored at vertList[x-1]; 
    //  for example, vertex 1 in vertList[0], vertex 2 in vertList[1] and so on. 
		fileout = filename;
		ifstream ifs(filename.c_str());
		int vertnum;
		ifs>>vertnum;
		for(int i=0;i<vertnum;i++) // push vertex IDs into the vertex vector before assigning the in and out list
		{
			Vertex *vert = new Vertex(i+1);	//Make new vectors
			vertList.push_back(vert);
		}
		while (!ifs.eof())	{
		int svert,evert,weit; 
		string line;
		ifs>>svert; 
		while(svert!=-1)
		{
			ifs>>evert; 
			while(evert!=-1)
			{
				ifs>>weit; // one weight means one edge
				int w = weit;
                Edge *tempedge = new Edge(vertList[svert-1],vertList[evert-1],weit); // new edge
				edgeList.push_back(tempedge);				
				vertList[svert-1]->outList.push_back(tempedge);
				vertList[evert-1]->inList.push_back(tempedge);
				ifs>>evert; 	
				int e = evert;
				if (w <= -1 && e == -1) {throw "Negative edge found";}				
			}
			ifs>>svert; 
		}
		ifs.close();
	}
}
	~Graph() {
		for(int i = 0; i < vertList.size(); i++)
			delete vertList[i];
		for(int i = 0; i < edgeList.size(); i++)
			delete edgeList[i];
	}
  int getSize() {return vertList.size();}
  
  // There is no need of addEdge and addVertex if using the constructor
  
  vector<Vertex*> getVertices()			{return vertList;}
  vector<Edge*> getOutEdges(int vertID)	{return vertList[vertID]->getOutEdges();}
  vector<Edge*> getInEdges(int vertID)	{return vertList[vertID]->getInEdges();}
  Vertex* getVertex(int vertID)		{return vertList[vertID];}  
  Edge* getEdge(int sVertID, int dVertID)
  {
	//returns a pointer
	for (int i = 0; i < vertList[sVertID]->getOutEdges().size(); i++)
	{
		if (vertList[sVertID]->getOutEdges()[i]->geteVertP() == vertList[dVertID])
		return vertList[sVertID]->getOutEdges()[i];
	}
  }
	void PrintGraph() // print out all the edges in the entire graph
	{
		cout << "Input graph: " << endl;
		ifstream ifs(fileout.c_str());
		string line;
		if(ifs.is_open()) 
		{
			while(getline(ifs, line)) {cout << line << endl;}
			ifs.close();
		}
		else cout << "Unable to open file";
		cout << endl;
	}
};
#endif