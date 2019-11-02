#include "BinaryTree.h"

int max3(int a, int b, int c)
{
	return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

//BinaryTree::private

void BinaryTree::setLeft(BinaryTree* left) { this->l = left; }

void BinaryTree::setRight(BinaryTree* right) { this->r = right; }

void BinaryTree::setParent(BinaryTree* parent) { this->p = parent; }

//BinaryTree::public

BinaryTree::BinaryTree() :
	v(0), l(NULL), r(NULL), p(NULL)
{}

BinaryTree::BinaryTree(int value) :
	v(value), l(NULL), r(NULL), p(NULL)
{}

BinaryTree::BinaryTree(int value, BinaryTree* left, BinaryTree* right, BinaryTree* parent) :
	v(value), l(left), r(right), p(parent)
{}

int BinaryTree::getValue() { return this->v; }

BinaryTree* BinaryTree::getLeft() { return this->l; }

BinaryTree* BinaryTree::getRight() { return this->r; }

BinaryTree* BinaryTree::getParent() { return this->p; }

void BinaryTree::setValue(int value) { this->v = value; }

BinaryTree* BinaryTree::search(int value)
{
	if (this->getValue() == value) return this;

	if (this->getLeft() != NULL) 
	{
		BinaryTree* bt = this->getLeft()->search(value);
		if (bt != NULL) return bt;
	}

	if (this->getRight() != NULL)
	{
		BinaryTree* bt = this->getRight()->search(value);
		if (bt != NULL) return bt;
	}

	return NULL;
}

void BinaryTree::add(int ip, int ic, const std::string& pos)
{
	BinaryTree* parent = this->BinaryTree::search(ip);

	if (parent == NULL)
	{
		std::cout << "not found " << ip << " " << ic << "\n";
		return;
	}

	BinaryTree* node = new BinaryTree(ic, NULL, NULL, parent);
	if (pos.compare("R") == 0) { parent->setRight(node); }
	if (pos.compare("L") == 0) { parent->setLeft(node); }

	return;
}

int BinaryTree::maxPathSum(int& mtl)
{
	int lmtl = 0, rmtl = 0;
	int lmps = INT_MIN, rmps = INT_MIN;
	int mps = INT_MIN;

	if (this->getLeft() != NULL) lmps = this->getLeft()->maxPathSum(lmtl);
	if (this->getRight() != NULL) rmps = this->getRight()->maxPathSum(rmtl);

	if (this->getLeft() != NULL && this->getRight() != NULL) mps = max3(this->getValue() + lmtl + rmtl, lmps, rmps);

	mtl = this->getValue() + std::max(lmtl, rmtl);

	return mps;
}

void BinaryTree::inorderTraversal(std::function<void(BinaryTree*)> fun)
{
	if (this->getLeft() != NULL) this->getLeft()->inorderTraversal(fun);
	fun(this);
	if (this->getRight() != NULL) this->getRight()->inorderTraversal(fun);
}