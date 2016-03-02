/*
	Howard Cheng
	CSCE 221 - 504
	PQComp.h
*/

#include "Item.h"

template<typename ElemType>
class PQComp {
public:
  int operator()(const Item<ElemType>& e1, const Item<ElemType>& e2) const {
    return e1.getKey() - e2.getKey();
  }
};