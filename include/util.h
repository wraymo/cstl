#pragma once
#define RED 0
#define BLACK 1
#define SUCCESS 0
#define MAP_NOT_INITIALIZED 1
#define SET_NOT_INITIALIZED 2
#define MEMORY_ERROR 3
#define FIND_ERROR 4

typedef int  (*compare)(const void*, const void*);
typedef int key_type;
typedef int value_type;
typedef struct iterator {
	const void* (*findNext)(struct iterator* pIterator);
	void (*replaceCurrentValue)(struct iterator* pIterator, value_type new_value, size_t size);
	const void* (*currentKey)(struct iterator* pIterator);
	const void* (*currentValue)(struct iterator* pIterator);
	void* pContainer;
	void* current_element;
} iterator;
