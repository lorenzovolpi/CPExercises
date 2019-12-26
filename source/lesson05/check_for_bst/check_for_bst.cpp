#include <iostream>
#include <vector>
#include <functional>
#include <climits>
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

int main()
{
	int test_cases = 0;
	std::cin >> test_cases;

	bst* root = NULL;

	for (int i = 0; i < test_cases; ++i)
	{
		int edges = 0;
		std::cin >> edges;

		for (int j = 0; j < edges; ++j)
		{
			int p = 0, c = 0;
			std::string pos = "";
			std::cin >> p;
			std::cin >> c;
			std::cin >> pos;

			if (root == NULL) root = new bst(p);

			root->add(p, c, pos);
		}

		int last = INT_MIN;
		if (root->checkBst(last)) std::cout << 1;
		else std::cout << 0;

		std::cout << std::endl;

		root = NULL;
	}
}
