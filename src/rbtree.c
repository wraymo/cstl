#include<stdio.h>
#include<stdlib.h>
#include "../include/rbtree.h"
#include "../include/util.h"

void leftRotate(rb* rbtree, rb_node* node)
{
	rb_node* right = node->right;

	node->right = right->left;

	if (node->right != NULL)
		node->right->parent = node;

	right->parent = node->parent;

	if (node->parent == NULL)
		rbtree->root = right;

	else if (node == node->parent->left)
		node->parent->left = right;

	else
		node->parent->right = right;

	right->left = node;
	node->parent = right;
}

void rightRotate(rb * rbtree, rb_node * node)
{
	rb_node* left = node->left;

	node->left = left->right;

	if (node->left != NULL)
		node->left->parent = node;

	left->parent = node->parent;

	if (node->parent == NULL)
		rbtree->root = left;

	else if (node == node->parent->left)
		node->parent->left = left;

	else
		node->parent->right = left;

	left->right = node;
	node->parent = left;
}

rb_node * BSTInsert(rb_node * root, compare func_comp, rb_node * new_node)
{
	if (!root)
		return new_node;

	if (func_comp(&new_node->key, &root->key) < 0)
	{
		root->left = BSTInsert(root->left, func_comp, new_node);
		root->left->parent = root;
	}
	else if (func_comp(&new_node->key, &root->key) > 0)
	{
		root->right = BSTInsert(root->right, func_comp, new_node);
		root->right->parent = root;
	}
	return root;
}

void fixViolation(rb * rbtree, rb_node * new_node)
{
	rb_node* root = rbtree->root;
	rb_node* parent = NULL;
	rb_node* grandparent = NULL;
	rb_node* temp = new_node;

	while ((temp != root) && (temp->color == RED) && (temp->parent->color == RED))// temp has grandparent
	{
		parent = temp->parent;
		grandparent = temp->parent->parent;

		if (parent == grandparent->left)
		{
			rb_node* uncle = grandparent->right;

			if (uncle != NULL && uncle->color == RED)
			{
				grandparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				temp = grandparent;
			}
			else
			{
				if (temp == parent->right)
				{
					leftRotate(rbtree, parent);
					temp = parent;
					parent = temp->parent;
				}

				rightRotate(rbtree, grandparent);

				int color_temp;
				color_temp = parent->color;
				parent->color = grandparent->color;
				grandparent->color = color_temp;
				temp = parent;
			}
		}
		else
		{
			rb_node* uncle = grandparent->left;

			if (uncle != NULL && uncle->color == RED)
			{
				grandparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				temp = grandparent;
			}
			else
			{
				if (temp == parent->left)
				{
					rightRotate(rbtree, parent);
					temp = parent;
					parent = temp->parent;
				}

				leftRotate(rbtree, grandparent);

				int color_temp;
				color_temp = parent->color;
				parent->color = grandparent->color;
				grandparent->color = color_temp;
				temp = parent;
			}
		}
	}
	rbtree->root->color = BLACK;
}

int RBTInsert(rb * rbtree, key_type key, value_type value)
{
	rb_node* new_node = (rb_node*)malloc(sizeof(rb_node));
	if (!new_node)
		return MEMORY_ERROR;
	new_node->key = key;
	new_node->value = value;
	new_node->parent = new_node->left = new_node->right = NULL;
	new_node->color = RED;
	rbtree->root = BSTInsert(rbtree->root, rbtree->func_comp, new_node);
	fixViolation(rbtree, new_node);
	return SUCCESS;
}

rb_node* search(rb_node * root, key_type data, compare func_comp)
{
	rb_node* temp = root;
	while (temp)
	{
		if (func_comp(&data, &temp->key) < 0)
			temp = temp->left;
		else if (func_comp(&data, &temp->key) == 0)
			break;
		else
			temp = temp->right;
	}

	return temp;
}

rb_node* findReplaceNode(rb_node * node)
{
	if (node->left && node->right)
		if (node->right->left)
			return node->right->left;
		else
			return node->right;

	if (!node->left && !node->right)
		return NULL;

	if (node->left)
		return node->left;

	return node->right;
}

void fixDoubleBlack(rb * rbtree, rb_node * node)
{
	rb_node* root = rbtree->root;
	if (node == root)
		return;

	rb_node * parent = node->parent;
	rb_node * sibling;

	if (!parent)
		sibling = NULL;
	else if (parent->left == node)
		sibling = parent->right;
	else
		sibling = parent->left;

	if (sibling == NULL)
		fixDoubleBlack(rbtree, parent);
	else // has sibling
	{
		if (sibling->color == RED)
		{
			parent->color = RED;
			sibling->color = BLACK;
			if (sibling == parent->left)
				rightRotate(rbtree, parent);
			else
				leftRotate(rbtree, parent);
			fixDoubleBlack(rbtree, node);
		}
		else // sibling is black
		{
			if (sibling->left && sibling->left->color == RED)
			{
				if (sibling == parent->left)  // left left
				{
					sibling->left->color = sibling->color;
					sibling->color = parent->color;
					rightRotate(rbtree, parent);
				}
				else // right left
				{
					sibling->left->color = parent->color;
					rightRotate(rbtree, sibling);
					leftRotate(rbtree, parent);
				}
				parent->color = BLACK;
			}
			else if (sibling->right && sibling->right->color == RED)
			{
				if (sibling == parent->left) // left right 
				{
					sibling->right->color = parent->color;
					leftRotate(rbtree, sibling);
					rightRotate(rbtree, parent);
				}
				else // right right 
				{
					sibling->right->color = sibling->color;
					sibling->color = parent->color;
					leftRotate(rbtree, parent);
				}
				parent->color = BLACK;
			}
			else // Two black children
			{
				sibling->color = RED;
				if (parent->color == BLACK)
					fixDoubleBlack(rbtree, parent);
				else
					parent->color = BLACK;
			}
		}
	}
}

void deleteNode(rb * rbtree, rb_node * delete_node)
{
	rb_node* root = rbtree->root;
	rb_node* replace_node = findReplaceNode(delete_node);
	rb_node* parent = delete_node->parent;

	if (!replace_node) //delete_node is the leaf
	{
		if (delete_node == root) // only one node in the tree
			rbtree->root = NULL;
		else
		{
			if (delete_node->color == BLACK) //both black
				fixDoubleBlack(rbtree, delete_node);
			else
			{
				rb_node* sibling;
				if (!parent)
					sibling = NULL;
				else if (parent->left == delete_node)
					sibling = parent->right;
				else
					sibling = parent->left;

				if (sibling)
					sibling->color = RED;
			}

			if (parent->left == delete_node)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		free(delete_node);
		return;
	}

	if (!delete_node->left || !delete_node->right) // delete_node has one child
	{
		if (delete_node == root)
		{
			delete_node->key = replace_node->key;
			delete_node->value = replace_node->value;
			delete_node->left = delete_node->right = NULL;
			free(replace_node);
		}
		else
		{
			int is_double_black = replace_node->color == BLACK && delete_node->color == BLACK;
			if (parent->left == delete_node)
				parent->left = replace_node;
			else
				parent->right = replace_node;
			free(delete_node);
			replace_node->parent = parent;
			if (is_double_black)
				fixDoubleBlack(rbtree, replace_node);
			else
				replace_node->color = BLACK;
		}
		return;
	}

	int temp_value = delete_node->value;
	delete_node->value = replace_node->value;
	replace_node->value = temp_value;
	int temp_key = delete_node->key;
	delete_node->key = replace_node->key;
	replace_node->key = temp_key;
	deleteNode(rbtree, replace_node);
}

int RBTDelete(rb * rbtree, key_type data)
{
	rb_node* delete_node = search(rbtree->root, data, rbtree->func_comp);
	if (delete_node)
	{
		deleteNode(rbtree, delete_node);
		return SUCCESS;
	}
	return FIND_ERROR;
}

rb* rbCreate(compare func_comp)
{
	rb* rbtree = (rb*)malloc(sizeof(rb));
	if (rbtree == NULL) {
		return NULL;
	}

	rbtree->func_comp = func_comp;
	rbtree->root = NULL;
	return rbtree;
}

void RBTClear(rb_node * root)
{
	if (root)
	{
		RBTClear(root->left);
		RBTClear(root->right);
		free(root);
	}
}

rb_node* RBTMinimum(rb * rbtree)
{
	if (rbtree == NULL || rbtree->root == NULL)
		return NULL;
	rb_node * temp = rbtree->root;
	while (temp->left)
		temp = temp->left;
	return temp;
}

rb_node* RBTMaximum(rb * rbtree)
{
	if (rbtree == NULL || rbtree->root == NULL)
		return NULL;
	rb_node * temp = rbtree->root;
	while (temp->right)
		temp = temp->right;
	return temp;
}

rb_node* RBTSuccessor(rb * rbtree, void* element)
{
	rb_node* temp = (rb_node*)element;
	if (!temp)
		return RBTMinimum(rbtree);
	if (temp->right)
	{
		temp = temp->right;
		while (temp->left)
			temp = temp->left;
		return temp;
	}

	if (temp->parent && temp == temp->parent->left)
		return temp->parent;

	while (temp->parent && temp == temp->parent->right)
		temp = temp->parent;

	return temp->parent;
}

rb_node * RBTPredecessor(rb * rbtree, void* element)
{
	rb_node* temp = (rb_node*)element;
	if (!temp)
		return RBTMaximum(rbtree);
	if (temp->left)
	{
		temp = temp->left;
		while (temp->right)
			temp = temp->right;
		return temp;
	}

	if (temp->parent && temp == temp->parent->right)
		return temp->parent;

	while (temp->parent && temp == temp->parent->left)
		temp = temp->parent;

	return temp->parent;
}

int RBTSize(rb_node * root)
{
	if (!root)
		return 0;
	int lsize = RBTSize(root->left);
	int rsize = RBTSize(root->right);
	return 1 + lsize + rsize;
}


void print(rb_node * root, int times)
{
	if (!root)
		return;
	print(root->right, times + 1);
	int i;
	for (i = 0; i < times; i++)
		printf("          ");
	printf("%d,%d(%d)\n", root->key, root->value, root->color);
	print(root->left, times + 1);
}
/*
int main()
{
	rb* tree = (rb*)malloc(sizeof(rb));
	tree->root = NULL;
	RBTInsert(tree, 25);
	print(tree->root, 0); putchar('\n');
	RBTInsert(tree, 35);
	print(tree->root, 0); putchar('\n');
	RBTInsert(tree, 30);
	print(tree->root, 0); putchar('\n');
	RBTInsert(tree, 10);
	print(tree->root, 0); putchar('\n');
	RBTInsert(tree, 40);
	print(tree->root, 0); putchar('\n');
	RBTInsert(tree, 20);
	print(tree->root, 0); putchar('\n');
	printf("delete\n");
	RBTDelete(tree, 30);
	print(tree->root, 0); putchar('\n');
	RBTDelete(tree, 25);
	print(tree->root, 0); putchar('\n');
	RBTDelete(tree, 35);
	print(tree->root, 0); putchar('\n');
}
*/