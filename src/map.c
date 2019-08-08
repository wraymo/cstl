#include "../include/rbtree.h"
#include "../include/map.h"
#include "../include/util.h"
#include<stdio.h>

map* newMap(compare func_comp)
{
	map* Map = (map*)malloc(sizeof(map));
	if (!Map)
		return NULL;

	Map->rbtree = rbCreate(func_comp);
	if (!Map->rbtree)
		return NULL;
	return Map;
}

int mapInsert(map* Map, key_type key, value_type value)
{
	if (!Map || !Map->rbtree)
		return MAP_NOT_INITIALIZED;
	return RBTInsert(Map->rbtree, key, value);
}

int mapEraseByKey(map * Map, key_type key)
{
	if (!Map || !Map->rbtree)
		return MAP_NOT_INITIALIZED;
	return RBTDelete(Map->rbtree, key);
}

int mapEraseByIter(map * Map, iterator * itr)
{
	if (!Map || !Map->rbtree)
		return MAP_NOT_INITIALIZED;
	return RBTDelete(Map->rbtree, mapGetKey(itr));
}

int mapEmpty(map * Map)
{
	if (Map && Map->rbtree && Map->rbtree->root)
		return 0;
	return 1;
}

int mapSize(map * Map)
{
	if (Map && Map->rbtree)
		return RBTSize(Map->rbtree->root);
	return 0;
}

int mapExist(map * Map, key_type key)
{
	if (!Map && !Map->rbtree)
		return MAP_NOT_INITIALIZED;
	if (search(Map->rbtree->root, key, Map->rbtree->func_comp))
		return SUCCESS;
	else
		return FIND_ERROR;
}

void mapClear(map * Map)
{
	if (Map && Map->rbtree)
	{
		RBTClear(Map->rbtree->root);
		Map->rbtree->root = NULL;
	}
}

void mapDelete(map * Map)
{
	mapClear(Map);
	if (Map)
	{
		if (Map->rbtree)
			free(Map->rbtree);
		free(Map);
	}
}

value_type mapGetValueByKey(map * Map, key_type key)
{
	if (Map && Map->rbtree)
	{
		rb_node* find = search(Map->rbtree->root, key, Map->rbtree->func_comp);
		if (find)
			return find->value;
	}
}

int mapSwap(map * Map1, map * Map2)
{
	if (!Map1 || !Map2)
		return MAP_NOT_INITIALIZED;
	rb * temp = Map1->rbtree;
	Map1->rbtree = Map2->rbtree;
	Map2->rbtree = temp;
	return SUCCESS;
}

rb_node* mapMinimum(map * Map)
{
	return RBTMinimum(Map->rbtree);
}

rb_node* mapSuccessor(map * Map, void* current_element)
{
	return RBTSuccessor(Map->rbtree, current_element);
}

rb_node* mapPredecessor(map * Map, void* current_element)
{
	return RBTPredecessor(Map->rbtree, current_element);
}

rb_node* mapFindNext(iterator * itr)
{
	map* Map = (map*)itr->pContainer;
	rb_node* ptr = NULL;

	if (!itr->current_element)
		itr->current_element = mapMinimum(Map);
	else
		itr->current_element = mapSuccessor(Map, itr->current_element);
	return (rb_node*)itr->current_element;
}

key_type mapGetKey(iterator * itr)
{
	rb_node* current = (rb_node*)itr->current_element;
	if (current)
		return current->key;
	else
		return mapFindNext(itr)->key;
}

value_type mapGetValueByIter(iterator * itr)
{
	rb_node* current = (rb_node*)itr->current_element;
	if (current)
		return current->value;
	else
		return mapFindNext(itr)->value;
}

void mapReplaceValue(iterator * itr, value_type value)
{
	map* Map = (map*)itr->pContainer;
	rb_node* current = (rb_node*)itr->current_element;
	current->value = value;
}

iterator* mapNewIterator(map * Map)
{
	iterator* itr = (iterator*)malloc(sizeof(iterator));
	itr->findNext = mapFindNext;
	itr->currentKey = mapGetKey;
	itr->currentValue = mapGetValueByIter;
	itr->replaceCurrentValue = mapReplaceValue;
	itr->pContainer = Map;
	itr->current_element = (void*)0;
	return itr;
}

void mapDeleteIterator(iterator * itr)
{
	if (itr)
		free(itr);
}

iterator* mapFind(map * Map, key_type key)
{
	iterator* itr = (iterator*)malloc(sizeof(iterator));
	itr->findNext = mapFindNext;
	itr->currentKey = mapGetKey;
	itr->currentValue = mapGetValueByIter;
	itr->replaceCurrentValue = mapReplaceValue;
	itr->pContainer = Map;
	itr->current_element = search(Map->rbtree->root, key, Map->rbtree->func_comp);
	return itr;
}

iterator* mapUpperBound(map * Map, key_type key)
{
	iterator* itr = (iterator*)malloc(sizeof(iterator));
	itr->findNext = mapFindNext;
	itr->currentKey = mapGetKey;
	itr->currentValue = mapGetValueByIter;
	itr->replaceCurrentValue = mapReplaceValue;
	itr->pContainer = Map;
	rb_node* current = search(Map->rbtree->root, key, Map->rbtree->func_comp);
	itr->current_element = mapSuccessor(Map, current);
	return itr;
}

iterator* mapLowerBound(map * Map, key_type key)
{
	iterator* itr = (iterator*)malloc(sizeof(iterator));
	itr->findNext = mapFindNext;
	itr->currentKey = mapGetKey;
	itr->currentValue = mapGetValueByIter;
	itr->replaceCurrentValue = mapReplaceValue;
	itr->pContainer = Map;
	rb_node* current = search(Map->rbtree->root, key, Map->rbtree->func_comp);
	itr->current_element = mapPredecessor(Map, current);
	return itr;
}

iterator* mapIteratorNext(iterator * itr)
{
	rb_node* current = NULL;
	map* Map = itr->pContainer;
	if (itr->current_element)
		current = search(Map->rbtree->root, mapGetKey(itr), Map->rbtree->func_comp);
	itr->current_element = mapSuccessor(itr->pContainer, current);
	return itr;
}

iterator* mapIteratorPrev(iterator * itr)
{
	rb_node* current = NULL;
	map* Map = itr->pContainer;
	if (itr->current_element)
		current = search(Map->rbtree->root, mapGetKey(itr), Map->rbtree->func_comp);
	itr->current_element = mapPredecessor(itr->pContainer, current);
	return itr;
}

