#pragma once
#ifndef BST__H
#define BST__H

#include <iostream>

class bst
{
private:
	int v;
	bst* l;
	bst* r;
	bst* p;

	void set_left(bst* left);
	void set_right(bst* right);
	void set_parent(bst* parent);

	static bool rec_check_bst(bst* root, int& last);

public:

	int get_value() { return this->v; }
	bst* get_left() { return this->l; }
	bst* get_right() { return this->r; }
	bst* get_parent() { return this->p; }

	bst();
	bst(int value);
	bst(int value, bst* left, bst* right, bst* parent);

	static bst* search(bst* root, int value);

	static bst* add(bst* root, int parent, int child, const std::string &pos);

	static bool check_bst(bst* root);

};





#endif // !BST__H
