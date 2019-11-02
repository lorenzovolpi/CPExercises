#pragma once
#ifndef BST__H
#define BST__H

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include "BinaryTree.h"

class Bst : public BinaryTree
{
public:

	Bst();
	Bst(int value);
	Bst(int value, Bst* left, Bst* right, Bst* parent);

	Bst* getLeft();
	Bst* getRight();
	Bst* getParent();

	BinaryTree* search(int value);
	
	using BinaryTree::add;

	void add(Bst* child);

	bool checkBst(int& last);

	static Bst* buildFromPreorder(Bst* root, std::vector<int> nums, int f, int l);

};





#endif // !BST__H

