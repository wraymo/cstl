#pragma once
#include<stdlib.h>
#include "util.h"

typedef struct rb_node {
	void* value_field;
	void* key_field;
	struct rb_node* left, * right, * parent;
	int color;
} rb_node;

typedef struct rb {
	rb_node* root;
	compare func_comp;
	size_t key_size;
	size_t value_size;
} rb;

extern rb* rbCreate(compare func_comp, size_t key_size, size_t value_size);
extern int RBTInsert(rb* rbtree, void* key_field, void* value_field);
extern int RBTDelete(rb* rbtree, void* data);
extern void RBTClear(rb_node* root);
extern rb_node* search(rb_node* root, void* key_field, compare func_comp);
extern rb_node* RBTMinimum(rb* rbtree);
extern rb_node* RBTSuccessor(rb* rbtree, void* element);
extern rb_node* RBTPredecessor(rb* rbtree, void* element);