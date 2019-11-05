#pragma once
#ifndef BINTREE__H
#define BINTREE__H

#include <iostream>
#include <functional>
#include <algorithm>

class bintree
{
private:

	int v;
	bintree* l;
	bintree* r;
	bintree* p;

protected:

	void setLeft(bintree* left);
	void setRight(bintree* right);
	void setParent(bintree* parent);

public:
	int getValue();
	bintree* getLeft();
	bintree* getRight();
	bintree* getParent();

	void setValue(int value);

	bintree(int value);
	bintree(int value, bintree* parent);
	bintree(int value, bintree* left, bintree* right, bintree* parent);

	virtual bintree* search(int value);

	void add(int parent, int child, const std::string& pos);

	int maxPathSum(int& mtl);

	void inorderTraversal(std::function<void(bintree*)> fun);

};

#endif // !BINARYTREE__H