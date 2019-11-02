#pragma once
#ifndef BINARYTREE__H
#define BINARYTREE__H

#include <iostream>
#include <functional>
#include <algorithm>

class BinaryTree
{
private:

	int v;
	BinaryTree* l;
	BinaryTree* r;
	BinaryTree* p;

protected:

	void setLeft(BinaryTree* left);
	void setRight(BinaryTree* right);
	void setParent(BinaryTree* parent);

public:
	int getValue();
	BinaryTree* getLeft();
	BinaryTree* getRight();
	BinaryTree* getParent();

	void setValue(int value);

	BinaryTree();
	BinaryTree(int value);
	BinaryTree(int value, BinaryTree* left, BinaryTree* right, BinaryTree* parent);

	virtual BinaryTree* search(int value);

	void add(int parent, int child, const std::string& pos);

	int maxPathSum(int& mtl);

	void inorderTraversal(std::function<void(BinaryTree*)> fun);

};

#endif // !BINARYTREE__H