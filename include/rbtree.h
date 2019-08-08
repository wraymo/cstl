#pragma once
#include<stdlib.h>
#include "util.h"

typedef struct rb_node {
	value_type value;
	key_type key;
	struct rb_node* left, * right, * parent;
	int color;
} rb_node;

typedef struct rb {
	rb_node* root;
	compare func_comp;
} rb;

extern rb* rbCreate(compare func_comp);
extern int RBTInsert(rb* rbtree, key_type key, value_type value);
extern int RBTDelete(rb* rbtree, key_type data);
extern void RBTClear(rb_node* root);
extern rb_node* search(rb_node* root, key_type key, compare func_comp);
extern rb_node* RBTMinimum(rb* rbtree);
extern rb_node* RBTSuccessor(rb* rbtree, void* element);
extern rb_node* RBTPredecessor(rb* rbtree, void* element);