#include "bst.h"

//Bst::public

Bst::Bst() : BinaryTree() {};

Bst::Bst(int value) : BinaryTree(value) {};

Bst::Bst(int value, Bst* left, Bst* right, Bst* parent) : BinaryTree(value, left, right, parent) {};

Bst* Bst::getLeft() { return (Bst*)BinaryTree::getLeft(); }

Bst* Bst::getRight() { return (Bst*)BinaryTree::getRight(); }

Bst* Bst::getParent() { return (Bst*)BinaryTree::getParent(); }

BinaryTree* Bst::search(int value)
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

void Bst::add(Bst* child)
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

bool Bst::checkBst(int& last)
{
	bool res = true;

	res = res & (this->getLeft() == NULL ? true : this->getLeft()->checkBst(last));
	if (this->getValue() < last) res = false;
	last = this->getValue();
	res = res & (this->getRight() == NULL ? true : this->getRight()->checkBst(last));

	return res;
}

Bst* Bst::buildFromPreorder(Bst* root, std::vector<int> nums, int f, int l)
{
	if (root == NULL) root = new Bst(nums[f]);

	int lf = f + 1, ll = f, rf = f + 1, rl = f;

	for (int i = lf; i <= l && nums[i] < nums[f]; i++) { ll = i; }

	rf = ll + 1;
	rl = l;

	if (lf <= ll) root->setLeft(new Bst(nums[lf], NULL, NULL, root));
	if (rf <= rl) root->setRight(new Bst(nums[rf], NULL, NULL, root));

	if (root->getLeft() != NULL) Bst::buildFromPreorder(root->getLeft(), nums, lf, ll);
	if (root->getRight() != NULL) Bst::buildFromPreorder(root->getRight(), nums, rf, rl);

	return root;
}




