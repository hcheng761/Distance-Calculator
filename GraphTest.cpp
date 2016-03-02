/*
	Howard Cheng
	CSCE 221 - 504
	GraphTest.cpp
*/

#include <climits>
#include <iostream>
#include <string>
#include <algorithm>
#include "Graph.h"
#include "PriorityQueue.h"
#include <stack>
using namespace std;

int main() 
{  	
		int comps=0;	//BH comparisons
		string txt;
		cout << "Enter name of txt file without extension: " << endl;
		cin >> txt;
		string str(txt + ".txt");
		Graph graph(str);
		graph.PrintGraph();
		
		int sVert, dVert;
		cout << "Enter the source vertex: " << endl;
		cin >> sVert;
		cout << "Enter the destination vertex: " << endl;
		cin >> dVert;
		cout << " " << endl;
		
		
		// for storing distances and extracting the minimum;  equivalent to Q and d[] on the slides
		PriorityQueue<int> pq;
		
		int size = graph.getSize();		//graph size
		int kArray[size];
		for(int i = 0; i < size; i++)	 {kArray[i] = INT_MAX;}	//key/weight
		int xArray[size];
		for(int i = 1; i <= size; i++) {xArray[i-1] = i;}		//element
		
		pq.createPriorityQueue(kArray, xArray, xArray, size);
		// for storing the parent (previous node) on the path; equivalent to pi[] on the slides
		int* shortestPathParent = new int[size + 1];
		for(int i = 0; i < size; i++) 	{shortestPathParent[i] = 0;}
		
		
		// Dijkstra's algorithm
		Locator sl = pq.getLocator(sVert);	//locator keeps track of element's memory address
		pq.replaceKey(sl,0);
		if(sVert > size || dVert > size || sVert < 0 || dVert < 0) throw "No such vertex exists";
		vector<Vertex*> del; // removed vertices
		vector<Vertex*> vertList = graph.getVertices();
		
		while( !pq.isEmpty()) {
			Vertex* u = vertList[pq.minElement() - 1];
			Locator locu = pq.getLocator(u->getID());
			int ukey = pq.getKey(locu);
			pq.removeMin();
			del.push_back(u);
			vector<Edge*> edges = u->getOutEdges();
			for( int i = 0; i < edges.size(); i++ ) {
				Vertex* v = edges[i] -> geteVertP();
				int w = edges[i] -> getWeight();
				Locator locv = pq.getLocator(v->getID());
				if(comps++, pq.getKey(locv) > (ukey + w)) 			//if (d[b] > d[a] + w(a,b))
				{
					pq.replaceKey(locv, ukey + w);		  			//d[b] = d[a] + w(a,b)
					shortestPathParent[v->getID()] = u->getID();	//P[b] = a
				}
			}
		}
	
		Vertex* d = graph.getVertex(dVert);
		Vertex* s = graph.getVertex(sVert);
		vector<int>vers, wt;
		vector<Edge*> e = vertList[dVert-1]->getInEdges();
		int c = 0;
		vers.push_back(dVert);
		if (sVert == dVert)
		{
			vers.push_back(dVert);
			wt.push_back(0);
		}
		else
		{
			while (c != sVert)
			{
				//compare edges
				int minw = e[0]->getWeight();
				int minv = e[0]->getsVertP()->getID();

				for (int i = 0; i < e.size(); i++)
				{
					if(e[i]->getWeight() < minw)
					{
						minw = e[i]->getWeight();
						minv = e[i]->getsVertP()->getID();
					}
				}
				wt.push_back(minw);
				vers.push_back(minv);
				c = vertList[minv-1]->getID();
				e = vertList[minv-1]->getInEdges();
			}
		reverse(wt.begin(),wt.end());
		reverse(vers.begin(),vers.end());
		}
		for (int i = 0; i < vers.size()-1; i++)
		{
			cout << vers[i] << "--[" << wt[i] << "]-->";
		}
			cout << dVert << endl;
			
		int dist = 0;
		for (int i = 0; i < wt.size(); i++)
		{
			dist = dist + wt[i];
		}
		cout << " " << endl;
		cout << "Total weight of the shortest path from " << sVert << " to " << dVert << " = " << dist << endl;
		cout << "Total number of comparisons needed to decrease key values: " << comps;
		
		return 0;
	}