#include "rbtree.h"

typedef struct map
{
	rb* rbtree;
} map;

extern map* newMap(compare func_comp, size_t key_size, size_t value_size);
extern int mapInsert(map* Map, const void* key_field, const void* value_field);
extern int mapEraseByKey(map* Map, void* key_field);
extern int mapEraseByIter(map* Map, iterator* itr);
extern int mapExist(map* Map, void* key_field);
extern int mapEmpty(map* Map);
extern int mapSize(map* Map);
extern int mapSwap(map* Map1, map* Map2);
extern void mapClear(map* Map);
extern void mapDelete(map* Map);
extern void mapReplaceValue(iterator* itr, void* value_field);
extern void mapDeleteIterator(iterator* itr);
extern rb_node* mapMinimum(map* Map);
extern rb_node* mapSuccessor(map* Map, void* current_element);
extern rb_node* mapPredecessor(map* Map, void* current_element);
extern rb_node* mapFindNext(iterator* itr);
extern void* mapGetKey(iterator* itr);
extern void* mapGetValueByKey(map* Map, void* key_field);
extern void* mapGetValueByIter(iterator* itr);
extern iterator* mapNewIterator(map* Map);
extern iterator* mapFind(map* Map, void* key_field);
extern iterator* mapUpperBound(map* Map, void* key_field);
extern iterator* mapLowerBound(map* Map, void* key_field);
extern iterator* mapIteratorNext(iterator* itr);
extern iterator* mapIteratorPrev(iterator* itr);