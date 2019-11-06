#pragma once
#ifndef BST__H
#define BST__H

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include "bintree.h"

class bst : public bintree
{
public:

	bst(int value);
	bst(int value, bst* parent);
	bst(int value, bst* left, bst* right, bst* parent);

	bst* getLeft();
	bst* getRight();
	bst* getParent();

	bintree* search(int value);
	
	using bintree::add;

	void add(bst* child);

	bool checkBst(int& last);

	static bst* buildFromPreorder(bst* root, std::vector<int> nums, int f, int l);

};

#endif // !BST__H

