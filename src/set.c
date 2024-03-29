#include "../include/rbtree.h"
#include "../include/set.h"
#include "../include/util.h"

set* newSet(compare func_comp, size_t key_size)
{
	set* Set = (set*)malloc(sizeof(set));
	if (!Set)
		return NULL;

	Set->rbtree = rbCreate(func_comp, key_size, 0);
	if (!Set->rbtree)
		return NULL;
	return Set;
}

int setInsert(set* Set, void* key_field)
{
	if (!Set || !Set->rbtree)
		return SET_NOT_INITIALIZED;
	return RBTInsert(Set->rbtree, key_field, NULL);
}

int setEraseByKey(set * Set, void* key_field)
{
	if (!Set || !Set->rbtree)
		return SET_NOT_INITIALIZED;
	return RBTDelete(Set->rbtree, key_field);
}

int setEraseByIter(set * Set, iterator * itr)
{
	if (!Set || !Set->rbtree)
		return SET_NOT_INITIALIZED;
	int status = RBTDelete(Set->rbtree, setGetKey(itr));
	itr->current_element = NULL;
	itr->current_element = setFindNext(itr);
	return status;
}

int setExist(set * Set, void* key_field)
{
	if (!Set || !Set->rbtree)
		return SET_NOT_INITIALIZED;
	if (search(Set->rbtree->root, key_field, Set->rbtree->func_comp))
		return SUCCESS;
	else
		return FIND_ERROR;
}

int setEmpty(set * Set)
{
	if (Set && Set->rbtree && Set->rbtree->root)
		return 0;
	return 1;
}

int setSize(set * Set)
{
	if (Set && Set->rbtree)
		return RBTSize(Set->rbtree->root);
	return 0;
}

void setClear(set * Set)
{
	if (Set && Set->rbtree)
	{
		RBTClear(Set->rbtree->root);
		Set->rbtree->root = NULL;
	}
}

void setDelete(set * Set)
{
	mapClear(Set);
	if (Set)
	{
		if (Set->rbtree)
			free(Set->rbtree);
		free(Set);
	}
}

int setSwap(set * Set1, set * Set2)
{
	if (!Set1 || !Set2)
		return SET_NOT_INITIALIZED;
	rb * temp = Set1->rbtree;
	Set1->rbtree = Set2->rbtree;
	Set2->rbtree = temp;
	return SUCCESS;
}

rb_node* setMinimum(set * Set)
{
	return RBTMinimum(Set->rbtree);
}

rb_node* setSuccessor(set * Set, void* current_element)
{
	return RBTSuccessor(Set->rbtree, current_element);
}

rb_node* setPredecessor(set * Set, void* current_element)
{
	return RBTPredecessor(Set->rbtree, current_element);
}

rb_node* setFindNext(iterator * itr)
{
	set* Set = (set*)itr->pContainer;
	rb_node* ptr = NULL;

	if (!itr->current_element)
		itr->current_element = setMinimum(Set);
	else
		itr->current_element = setSuccessor(Set, itr->current_element);
	return (rb_node*)itr->current_element;
}

void* setGetKey(iterator * itr)
{
	rb_node* current = (rb_node*)itr->current_element;
	if (current)
		return current->key_field;
	else
		return setFindNext(itr)->key_field;
}

iterator* setNewIterator(set * Set)
{
	iterator* itr = (iterator*)malloc(sizeof(iterator));
	itr->findNext = setFindNext;
	itr->currentKey = setGetKey;
	itr->pContainer = Set;
	itr->current_element = (void*)0;
	return itr;
}

void setDeleteIterator(iterator * itr)
{
	if (itr)
		free(itr);
}

iterator* setFind(set * Set, void* key_field)
{
	iterator* itr = (iterator*)malloc(sizeof(iterator));
	itr->findNext = setFindNext;
	itr->currentKey = setGetKey;
	itr->pContainer = Set;
	itr->current_element = search(Set->rbtree->root, key_field, Set->rbtree->func_comp);
	return itr;
}

iterator* setUpperBound(set * Set, void* key_field)
{
	iterator* itr = (iterator*)malloc(sizeof(iterator));
	itr->findNext = setFindNext;
	itr->currentKey = setGetKey;
	itr->pContainer = Set;
	rb_node* current = search(Set->rbtree->root, key_field, Set->rbtree->func_comp);
	itr->current_element = setSuccessor(Set, current);
	return itr;
}

iterator* setLowerBound(set * Set, void* key_field)
{
	iterator* itr = (iterator*)malloc(sizeof(iterator));
	itr->findNext = setFindNext;
	itr->currentKey = setGetKey;
	itr->pContainer = Set;
	rb_node* current = search(Set->rbtree->root, key_field, Set->rbtree->func_comp);
	itr->current_element = setPredecessor(Set, current);
	return itr;
}

iterator* setIteratorNext(iterator * itr)
{
	rb_node* current = NULL;
	set* Set = itr->pContainer;
	if (itr->current_element)
		current = search(Set->rbtree->root, setGetKey(itr), Set->rbtree->func_comp);
	itr->current_element = setSuccessor(itr->pContainer, current);
	return itr;
}

iterator* setIteratorPrev(iterator * itr)
{
	rb_node* current = NULL;
	set* Set = itr->pContainer;
	if (itr->current_element)
		current = search(Set->rbtree->root, setGetKey(itr), Set->rbtree->func_comp);
	itr->current_element = setPredecessor(itr->pContainer, current);
	return itr;
}
