#include <iostream>
#include <vector>
#include <climits>
#include <functional>

/*
	The idea is to perform a postorder traversal. For each node perform the maximum path down to leaves
	as the sum of current data and maximum of the maximum for left and right to subtree. For each node the
	maximum path sum is computed as the maximum among mps of right and left subtrees and sum of current data,
	maximum path down to leaves of left and right subtree. The cost of this algorithm is O(n).

*/

struct bintree
{
	int v;
	bintree *l, *r, *p;

	bintree(int value) : v(value), l(NULL), r(NULL), p(NULL) {}
	bintree(int value, bintree* parent) : v(value), l(nullptr), r(nullptr), p(parent) {}
	bintree(int value, bintree* left, bintree* right, bintree* parent) : v(value), l(left), r(right), p(parent) {}

	bintree* bsearch(int value){
		if (this->v == value) return this;
		if (value < this->v)
		{
			if (this->l == NULL) return NULL;
			else this->l->bsearch(value);
		}
		if (value > this->v)
		{
			if (this->r == NULL) return NULL;
			else return this->r->bsearch(value);
		}
	}

	bintree* search(int value) {
		if (this->v == value) return this;
		bintree* res = this->l == NULL ? NULL : this->l->search(value);
		if(res == NULL) res = this->r == NULL ? NULL : this->r->search(value);
		return res;
	}

	void add(int ip, int ic, const std::string& pos) {
		bintree* parent = this->search(ip);

		if (parent == NULL) {
			return;
		}

		bintree* node = new bintree(ic, parent);
		if (pos.compare("R") == 0) { parent->r = node; }
		if (pos.compare("L") == 0) { parent->l = node; }
	}

	void inorderTraversal(std::function<void(bintree*)> fun) {
		if (this->l != NULL) this->l->inorderTraversal(fun);
		fun(this);
		if (this->r != NULL) this->r->inorderTraversal(fun);
	}

};

int max3(int a, int b, int c)
{
	return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

int max_path_sum(bintree* root, int& mtl) {
	int lmtl = 0, rmtl = 0;
	int lmps = INT_MIN, rmps = INT_MIN;
	int mps = INT_MIN;

	if (root->l != NULL) lmps = max_path_sum(root->l, lmtl);
	if (root->r != NULL) rmps = max_path_sum(root->r, rmtl);

	mps = max3(root->v + lmtl + rmtl, lmps, rmps);

	mtl = root->v + std::max(lmtl, rmtl);

	return mps;
}

int main()
{
	int test_cases = 0;
	std::cin >> test_cases;

	for (int i = 0; i < test_cases; ++i)
	{
		int n = 0;
		std::cin >> n;
		bintree* root = NULL;
		for (int j = 0; j < n; ++j)
		{
			int ip, ic;
			std::string pos;

			std::cin >> ip;
			std::cin >> ic;
			std::cin >> pos;

			if (root == NULL) root = new bintree(ip);

			root->add(ip, ic, pos);
		}

		int mtl = 0, mps = 0;

		mps = max_path_sum(root, mtl);

		std::cout << mps << std::endl;
	}
}