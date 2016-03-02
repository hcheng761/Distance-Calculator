/*
	Howard Cheng
	CSCE 221 - 504
	BinaryHeap.h
*/
#ifndef HEAP_H_
#define HEAP_H_

#include "PriorityQueue.h"
#include <stdexcept>
#include <iostream>
#include <vector>

using namespace std;

struct EmptyHeap : std::range_error {
    explicit EmptyHeap(char const* msg=NULL): range_error(msg) {}
};

template<typename ElemType, typename Comp>
class BinaryHeap {
private:
    Comp comp;									// Comp is a comparator class and comp(a,b) will compare arguments a and b
    int curSize;									// number of elements in heap
    ElemType *array;								// (dynamic) heap array
    int length;									// the length of the array
    vector<Locator> locVec; 						// locator vector
    static const int DEF_SIZE = 10;
	
    void getNewArray(int newSize) {
        array = new ElemType[newSize];
        length = newSize;
    }
    void checkSize() 
	{							// double the heap array if it is full
        if (curSize == length) 
		{
            ElemType *oldArray = array;
            getNewArray(2*curSize);
            for (int i = 0; i < curSize; i++)
                array[i] = oldArray[i];
            delete [] oldArray;
        }
    }
    
    void walkUp(int hole); 	   
    void walkDown(int hole);

public: 										// templated class BinaryHeap (cont) 
	int comparisons;
	ElemType getItem( int k ) { return array[k]; } 
	int size() { return curSize; }
	BinaryHeap(int size = DEF_SIZE) {
		comparisons = 0;
		curSize = 0;								//constructor
        getNewArray(size);
    }
    
    Locator findMin() throw (EmptyHeap) 
	{
        if ( isEmpty() ) throw EmptyHeap();
        return locVec[array[0].getlocIndex()];
    }
	
	Locator getLocator(int id)
	{	
		//cout << "getLocator: " << "(" << id << "," << locVec[id].getpqIndex() << ")" << endl;
		//if (locVec[id].getpqIndex() == -1)
		return locVec[id].getpqIndex();
		//else
		//return locVec[id].getpqIndex();
	}
	
	Locator findMinloc() throw (EmptyHeap) 
	{
        if ( isEmpty() ) throw EmptyHeap();
        return locVec[array[0].getlocIndex()];
    }
    
    bool isEmpty( ) const { return curSize == 0; }
    void insert(const ElemType& x);
    void deleteMin() throw (EmptyHeap);
    void toss(ElemType x); 						// (from Heap slides)
    void buildHeap(); 							// (from Heap slides)
	void printHeapLocators() {
		for(int i = 0; i < 9; i++) {
			cout << locVec[i] << endl;
		}
	}
	void deleteElem( int k ) throw (EmptyHeap) 
	{
		locVec[array[k].getElem()].setpqIndex( -1 );
		array[k] = array[ --curSize ];
		locVec[array[k].getElem()].setpqIndex( k );										
		if(comp(array[k],array[(k-1)/2]) < 0) {walkUp(k);}
		else if(comp(array[k],array[2*k+1]) > 0) {walkDown(k);}
	}
	void replace( Locator loc, int k ) throw (EmptyHeap) 
	{
		int place = loc.getpqIndex();	//getpqIndex() returns index in locator vector
		//cout << "Place: " << place << endl;
		array[place].setKey( k );
		if(comp(array[place], array[(place-1)/2]) < 0) {walkUp(place);} 
		else if(comp(array[place], array[2*place+1]) > 0) {
		//cout << "t" << endl;
		walkDown(place);}
	}
};

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::insert(const ElemType& x) {
    checkSize();
    int hole = curSize++;
    array[hole] = x;
	if(locVec.size() <= x.getlocIndex()) {
		for(int i = locVec.size(); i <= x.getlocIndex(); i++ ) 
		{			
			Locator l;
			locVec.push_back( l );
		}
	}
	locVec[x.getlocIndex()].setpqIndex(hole);
    walkUp(hole);
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::deleteMin() throw (EmptyHeap) 
{
	locVec[array[0].getElem()].setpqIndex( -1 );
	array[0] = array[ --curSize ];
	locVec[array[0].getElem()].setpqIndex( 0 );										
    walkDown(0);
}

												// (extracted from the original insert function)
template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::walkUp(int hole) 
{
	ElemType key = array[hole];
	comparisons += 1;
    for ( ; hole > 0 && comp(array[(hole-1)/2], key) > 0; hole = (hole-1)/2) 
	{
        comparisons += 1;						
		locVec[array[(hole-1)/2].getElem()].setpqIndex(array[hole].getlocIndex());
		array[hole] = array[(hole-1)/2];
    }
	key.setlocIndex(array[hole].getlocIndex());
    array[hole] = key;
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::walkDown(int hole) 
{
    int child;
    ElemType key = array[hole];
    for ( ; 2*hole+1 < curSize; hole = child) 
	{
        child = 2*hole+1;
		comparisons += 1;
        if (child != curSize-1 && comp(array[child], array[child+1]) > 0) 
		{
            comparisons += 1;
			child++;
		}
												// right child = 2*hole+2
        if (comp(key, array[child]) > 0) 
		{
			comparisons += 1;
            locVec[array[child].getlocIndex()].setpqIndex(hole);
			array[hole] = array[child];
        }
        else break;
    }
	locVec[key.getlocIndex()].setpqIndex( hole );
    array[hole] = key;
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::toss(ElemType x) 
{
    checkSize();
    array[ curSize++ ] = x;
	if(locVec.size() <= x.getlocIndex()) {
		for( int i = locVec.size(); i <= x.getlocIndex(); i++ ) 
		{
			Locator l;
			locVec.push_back( l );
		}
	}
	locVec[x.getlocIndex()].setpqIndex( curSize - 1 );
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::buildHeap() 
{
    locVec.resize(100);
	for (int i = (curSize-2)/2; i >= 0; i--) walkDown(i);
	cout << "Comparisons : " << comparisons << endl;
}
#endif /* HEAP_H_ */