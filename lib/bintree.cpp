#include "bintree.h"

int max3(int a, int b, int c)
{
	return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

//bintree::private

void bintree::setLeft(bintree* left) { this->l = left; }

void bintree::setRight(bintree* right) { this->r = right; }

void bintree::setParent(bintree* parent) { this->p = parent; }

//bintree::public

bintree::bintree(int value) :
	v(value), l(NULL), r(NULL), p(NULL)
{}

bintree::bintree(int value, bintree* parent) :
	v(value), l(nullptr), r(nullptr), p(parent)
{}

bintree::bintree(int value, bintree* left, bintree* right, bintree* parent) :
	v(value), l(left), r(right), p(parent)
{}

int bintree::getValue() { return this->v; }

bintree* bintree::getLeft() { return this->l; }

bintree* bintree::getRight() { return this->r; }

bintree* bintree::getParent() { return this->p; }

void bintree::setValue(int value) { this->v = value; }

bintree* bintree::search(int value)
{
	if (this->getValue() == value) return this;

	if (this->getLeft() != NULL) 
	{
		bintree* bt = this->getLeft()->search(value);
		if (bt != NULL) return bt;
	}

	if (this->getRight() != NULL)
	{
		bintree* bt = this->getRight()->search(value);
		if (bt != NULL) return bt;
	}

	return NULL;
}

void bintree::add(int ip, int ic, const std::string& pos)
{
	bintree* parent = this->bintree::search(ip);

	if (parent == NULL)
	{
		std::cout << "not found " << ip << " " << ic << "\n";
		return;
	}

	bintree* node = new bintree(ic, NULL, NULL, parent);
	if (pos.compare("R") == 0) { parent->setRight(node); }
	if (pos.compare("L") == 0) { parent->setLeft(node); }

	return;
}

int bintree::maxPathSum(int& mtl)
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

void bintree::inorderTraversal(std::function<void(bintree*)> fun)
{
	if (this->getLeft() != NULL) this->getLeft()->inorderTraversal(fun);
	fun(this);
	if (this->getRight() != NULL) this->getRight()->inorderTraversal(fun);
}