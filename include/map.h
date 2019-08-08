#include "rbtree.h"

typedef struct map
{
	rb* rbtree;
} map;

extern map* newMap(compare func_comp);
extern int mapInsert(map* Map, key_type key, value_type value);
extern int mapEraseByKey(map* Map, key_type key);
extern int mapEraseByIter(map* Map, iterator* itr);
extern int mapExist(map* Map, key_type key);
extern int mapEmpty(map* Map);
extern int mapSize(map* Map);
extern int mapSwap(map* Map1, map* Map2);
extern void mapClear(map* Map);
extern void mapDelete(map* Map);
extern void mapReplaceValue(iterator* itr, value_type value);
extern void mapDeleteIterator(iterator* itr);
extern rb_node* mapMinimum(map* Map);
extern rb_node* mapSuccessor(map* Map, void* current_element);
extern rb_node* mapPredecessor(map* Map, void* current_element);
extern rb_node* mapFindNext(iterator* itr);
extern key_type mapGetKey(iterator* itr);
extern value_type mapGetValueByKey(map* Map, key_type key);
extern value_type mapGetValueByIter(iterator* itr);
extern iterator* mapNewIterator(map* Map);
extern iterator* mapFind(map* Map, key_type key);
extern iterator* mapUpperBound(map* Map, key_type key);
extern iterator* mapLowerBound(map* Map, key_type key);
extern iterator* mapIteratorNext(iterator* itr);
extern iterator* mapIteratorPrev(iterator* itr);