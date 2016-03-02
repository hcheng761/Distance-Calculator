/*
	Howard Cheng
	CSCE 221 - 504
	Item.h
*/

template<typename ElemType>

class Item {
private:
  int key;
  ElemType elem;
  int locIndex; 								// or a vector index of the corresonding locator 
  
public:
  Item(const int k=0, const ElemType& e=ElemType(), int l=0): 
    key(k), elem(e), locIndex(l) { } 			//constructor
  const int getKey() const { return key; }
  const ElemType& getElem() const { return elem; }
  void setKey(const int k) { key = k; }
  void setElem(const ElemType& e) { elem = e; }
  int getlocIndex() const { return locIndex; }
  void setlocIndex(int k) { locIndex = k; }	
};

template<typename ElemType>
ostream& operator<<(ostream& out, Item<ElemType>& item) {
	out << "(" << item.getKey() << ", " << item.getElem() << ", " << item.getlocIndex() << ")";
	return out;
}