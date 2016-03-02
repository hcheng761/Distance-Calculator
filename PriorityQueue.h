/*
	Howard Cheng
	CSCE 221 - 504
	PriorityQueue.h
*/

#ifndef PRIORITY_H_
#define PRIORITY_H_

#include <cstdlib>
#include <iostream>
using namespace std;
template<typename ElemType> class Item;

class Locator {
private: 
  int pqIndex;
public:
  Locator( int i = -1 ): pqIndex(i) {}
  void setpqIndex(const int k) {pqIndex = k;}
  int getpqIndex() const {return pqIndex;}
};
												
ostream& operator<<(ostream& out, Locator& loc) 
{
	out << loc.getpqIndex();
	return out;
}

#include "PQComp.h"
#include <stdexcept>

struct EmptyPriorityQueue : std::range_error {
  explicit EmptyPriorityQueue(char const* msg=NULL): range_error(msg) {}
};

#include "BinaryHeap.h"
template<typename ElemType>
class PriorityQueue {
protected: 
  typedef Item<ElemType> _Item;
  typedef PQComp<ElemType> _PQComp;
  
private: 
  BinaryHeap<_Item, _PQComp> T;  
  static const int DEF_SIZE = 10;
  
public: 										// class PriorityQueue cont.
  PriorityQueue(int size = DEF_SIZE) : T(size) { }
  bool isEmpty() const { return T.isEmpty(); }
  BinaryHeap<_Item, _PQComp> getT() { return T; }
  Locator getLocator(int id) {return T.getLocator(id);}
  void replaceKey(Locator loc, int k) {T.replace(loc,k);}
  int getKey(Locator loc) {return T.getItem(loc.getpqIndex()).getKey();}
  Locator min() throw (EmptyPriorityQueue) {return T.findMin();}
  void remove(Locator loc) throw(EmptyPriorityQueue) {T.deleteElem(loc.getpqIndex());}
  
  void printlocVec() {T.printHeapLocators();}
  
  void createPriorityQueue(int kArray[], ElemType xArray[], int locIndexArray[], int n) 
  {
	for(int i = 0; i < n; i++) 
	{
		_Item it;
		it.setKey( kArray[i]);
		it.setElem( xArray[i]);
		it.setlocIndex(locIndexArray[i-1]);
		T.toss(it);
	}
	T.buildHeap();
  }
  
  void insertItem(const int k, const ElemType& e, int locIndex)
  { 
	_Item i;
	i.setKey(k);
	i.setElem(e);
	i.setlocIndex( locIndex );
	T.insert(i); 
  }
  
  const ElemType& minElement() throw (EmptyPriorityQueue) 
  {
    if (T.isEmpty())
    throw EmptyPriorityQueue();
    return T.getItem(T.findMin().getpqIndex()).getElem();								// Used to be getElem(0
  }
  
  const int minKey() throw (EmptyPriorityQueue) 
  {
    if (T.isEmpty()) throw EmptyPriorityQueue();
    return T.findMin().getKey();
  }
  void removeMin() throw (EmptyPriorityQueue) 
  {
    if (T.isEmpty())
    throw EmptyPriorityQueue();
    T.deleteMin();
  }  
};
												// output the priority queue
  template<typename ElemType>
  ostream& operator<<(ostream& out, PriorityQueue<ElemType>& pq) 
  {
	for( int i = 0; i < pq.getT().size(); i++ ) 
	{
		Item<int> test = pq.getT().getItem(i);
		out << test << endl;
	}
	return out;
  }
#endif /*PRIORITY_H_*/