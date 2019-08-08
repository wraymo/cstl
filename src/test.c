#include<stdio.h>
#include "../include/map.h"
#include "../include/set.h"

int Compare(const void* left, const void* right) {
	key_type l = *(key_type*)left;
	key_type r = *(key_type*)right;
	return l - r;
}

const int key[] = { 8, 6, 5, 2, 10, 3, 7, 1 };
const int value[] = { 28, 36, 75, 64, 53, 45, 12, 23 };

void testMap()
{
	map* Map = newMap(Compare);
	int i;
	for (i = 0; i < 8; i++)
		mapInsert(Map, key[i], value[i]);
	print(Map->rbtree->root, 0);
	mapEraseByKey(Map, 6);
	print(Map->rbtree->root, 0);
	mapEraseByKey(Map, 7);
	print(Map->rbtree->root, 0);
	printf("empty? %d\n", mapEmpty(Map));
	printf("size? %d\n", mapSize(Map));
	printf("exist 5? %d\n", mapExist(Map, 5));
	printf("exist 11? %d\n", mapExist(Map, 11));
	iterator * iter = mapNewIterator(Map);
	iter = mapIteratorNext(iter);
	printf("key? %d\n", mapGetKey(iter));
	mapEraseByIter(Map, iter);
	print(Map->rbtree->root, 0);
	iter = mapIteratorNext(iter);
	printf("key? %d\n", mapGetKey(iter));
	iter = mapIteratorPrev(iter);
	printf("key? %d\n", mapGetKey(iter));
	mapReplaceValue(iter, 89);
	print(Map->rbtree->root, 0);
	mapClear(Map);
	print(Map->rbtree->root, 0);
}

void testSet()
{
	set* Set = newSet(Compare);
	int i;
	for (i = 0; i < 8; i++)
		setInsert(Set, key[i]);
	print(Set->rbtree->root, 0);
	setEraseByKey(Set, 6);
	print(Set->rbtree->root, 0);
	setEraseByKey(Set, 7);
	print(Set->rbtree->root, 0);
	printf("empty? %d\n", setEmpty(Set));
	printf("size? %d\n", setSize(Set));
	printf("exist 5? %d\n", setExist(Set, 5));
	printf("exist 11? %d\n", setExist(Set, 11));
	iterator * iter = setNewIterator(Set);
	iter = setIteratorNext(iter);
	printf("key? %d\n", setGetKey(iter));
	iter = mapIteratorNext(iter);
	printf("key? %d\n", setGetKey(iter));
	iter = mapIteratorPrev(iter);
	printf("key? %d\n", setGetKey(iter));
	print(Set->rbtree->root, 0);
	setClear(Set);
	print(Set->rbtree->root, 0);
}

int main()
{
	testMap();
	//testSet();
}