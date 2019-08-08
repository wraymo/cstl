#include "rbtree.h"

typedef struct set
{
	rb* rbtree;
} set;

extern set* newSet(compare func_comp);
extern int setInsert(set* Set, key_type key);
extern int setEraseByKey(set* Set, key_type key);
extern int setExist(set* Set, key_type key);
extern int setEmpty(set* Set);
extern int setSize(set* Set);
extern int setSwap(set* Set1, set* Set2);
extern void setClear(set* Set);
extern void setDelete(set* Set);
extern void setDeleteIterator(iterator* itr);
extern rb_node* setMinimum(set* Set);
extern rb_node* setSuccessor(set* Set, void* current_element);
extern rb_node* setPredecessor(set* Set, void* current_element);
extern rb_node* setFindNext(iterator* itr);
extern key_type setGetKey(iterator* itr);
extern iterator* setNewIterator(set* Set);
extern iterator* setFind(set* Set, key_type key);
extern iterator* setUpperBound(set* Set, key_type key);
extern iterator* setLowerBound(set* Set, key_type key);
extern iterator* setIteratorNext(iterator* itr);
extern iterator* setIteratorPrev(iterator* itr);
