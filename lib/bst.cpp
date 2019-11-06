#include "bst.h"

//Bst::public

bst::bst(int value) : bintree(value) {};

bst::bst(int value, bst* parent) : bintree(value, parent) {};

bst::bst(int value, bst* left, bst* right, bst* parent) : bintree(value, left, right, parent) {};

bst* bst::getLeft() { return (bst*)bintree::getLeft(); }

bst* bst::getRight() { return (bst*)bintree::getRight(); }

bst* bst::getParent() { return (bst*)bintree::getParent(); }

bintree* bst::search(int value)
{
	if (this->getValue() == value) return this;
	if (value < this->getValue())
	{
		if (this->getLeft() == NULL) return NULL;
		else this->getLeft()->search(value);
	}
	if (value > this->getValue())
	{
		if (this->getRight() == NULL) return NULL;
		else return this->getRight()->search(value);
	}
}

void bst::add(bst* child)
{
	if (child->getValue() > this->getValue())
	{
		if (this->getRight() == NULL)
		{
			this->setRight(child);
			child->setParent(this);
		}
		else
		{
			this->getRight()->add(child);
		}
	}

	if (child->getValue() < this->getValue())
	{
		if (this->getLeft() == NULL)
		{
			this->setLeft(child);
			child->setParent(this);
		}
		else 
		{
			this->getLeft()->add(child);
		}
	}

	return;
}

bool bst::checkBst(int& last)
{
	bool res = true;

	res = res & (this->getLeft() == NULL ? true : this->getLeft()->checkBst(last));
	if (this->getValue() < last) res = false;
	last = this->getValue();
	res = res & (this->getRight() == NULL ? true : this->getRight()->checkBst(last));

	return res;
}

bst* bst::buildFromPreorder(bst* root, std::vector<int> nums, int f, int l)
{
	if (root == NULL) root = new bst(nums[f]);

	int lf = f + 1, ll = f, rf = f + 1, rl = f;

	for (int i = lf; i <= l && nums[i] < nums[f]; i++) { ll = i; }

	rf = ll + 1;
	rl = l;

	if (lf <= ll) root->setLeft(new bst(nums[lf], NULL, NULL, root));
	if (rf <= rl) root->setRight(new bst(nums[rf], NULL, NULL, root));

	if (root->getLeft() != NULL) bst::buildFromPreorder(root->getLeft(), nums, lf, ll);
	if (root->getRight() != NULL) bst::buildFromPreorder(root->getRight(), nums, rf, rl);

	return root;
}




