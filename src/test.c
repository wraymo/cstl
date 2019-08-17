#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "../include/map.h"
#include "../include/set.h"

int Compare(const void* left, const void* right) {
	int l = *(int*)left;
	int r = *(int*)right;
	return l - r;
}


const int key[] = { 8, 6, 5, 2, 10, 3, 7, 1 };
const int value[] = { 28, 36, 75, 64, 53, 45, 12, 23 };


void testMap()
{
	map* Map = newMap(Compare, sizeof(int), sizeof(int));
	int i;
	for (i = 0; i < 8; i++)
		mapInsert(Map, &key[i], &value[i]);
	print(Map->rbtree->root, 0); printf("\n\n\n");
	int a = 6, b = 7, c = 5, d = 11, e = 89;
	mapEraseByKey(Map, &a);
	print(Map->rbtree->root, 0); printf("\n\n\n");
	mapEraseByKey(Map, &b);
	print(Map->rbtree->root, 0); printf("\n\n\n");
	printf("empty? %d\n", mapEmpty(Map));
	printf("size? %d\n", mapSize(Map));
	printf("exist 5? %d\n", mapExist(Map, &c));
	printf("exist 11? %d\n", mapExist(Map, &d));
	iterator * iter = mapNewIterator(Map);
	iter = mapIteratorNext(iter);
	printf("key? %d\n", *(int*)mapGetKey(iter));
	mapEraseByIter(Map, iter);
	print(Map->rbtree->root, 0);
	iter = mapIteratorNext(iter);
	printf("key? %d\n", *(int*)mapGetKey(iter));
	iter = mapIteratorPrev(iter);
	printf("key? %d\n", *(int*)mapGetKey(iter));
	mapReplaceValue(iter, &e);
	print(Map->rbtree->root, 0);
	mapClear(Map);
	print(Map->rbtree->root, 0);
}

void testSet()
{
	set* Set = newSet(Compare, sizeof(int));
	int i;
	for (i = 0; i < 8; i++)
		setInsert(Set, &key[i]);
	print(Set->rbtree->root, 0); printf("\n\n");
	int a = 6, b = 7, c = 5, d = 11, e = 89;
	setEraseByKey(Set, &a);
	print(Set->rbtree->root, 0); printf("\n\n");
	setEraseByKey(Set, &b);
	print(Set->rbtree->root, 0); printf("\n\n");
	printf("empty? %d\n", setEmpty(Set));
	printf("size? %d\n", setSize(Set));
	printf("exist 5? %d\n", setExist(Set, &c));
	printf("exist 11? %d\n", setExist(Set, &d));
	iterator * iter = setNewIterator(Set);
	iter = setIteratorNext(iter);
	printf("key? %d\n", *(int*)setGetKey(iter));
	iter = mapIteratorNext(iter);
	printf("key? %d\n", *(int*)setGetKey(iter));
	iter = mapIteratorPrev(iter);
	printf("key? %d\n", *(int*)setGetKey(iter));
	print(Set->rbtree->root, 0);
	setClear(Set);
	print(Set->rbtree->root, 0);
}

int main()
{
	testMap();
	//testSet();
}
