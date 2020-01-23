#include <iostream>
#include <vector>
#include <functional>
#include <climits>
#include <algorithm>

/*
	The idea of this solution is to perform an inorder traversal of the tree
	and to keep in last the previous element in the traversal. If current element is
	grater than last answer is false, otherwise is true. The algorithm runs in O(n).
*/

struct bst
{
	int v;
	bst *l, *r, *p;

	bst(int value) : v(value), l(NULL), r(NULL), p(NULL) {}
	bst(int value, bst* parent) : v(value), l(nullptr), r(nullptr), p(parent) {}
	bst(int value, bst* left, bst* right, bst* parent) : v(value), l(left), r(right), p(parent) {}

	bst* bsearch(int value){
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

	bst* search(int value) {
		if (this->v == value) return this;
		bst* res = this->l == NULL ? NULL : this->l->search(value);
		if(res == NULL) res = this->r == NULL ? NULL : this-> r->search(value);
		return res;
	}
	
	void add(bst* child) {
		if (child->v > this->v)
		{
			if (this->r == NULL)
			{
				this->r = child;
				child->p = this;
			}
			else
			{
				this->r->add(child);
			}
		}

		if (child->v < this->v)
		{
			if (this->l == NULL)
			{
				this->l = child;
				child->p = this;
			}
			else 
			{
				this->l->add(child);
			}
		}

		return;
	}

	void add(int ip, int ic, const std::string& pos){
		bst* parent = this->search(ip);

		if (parent == NULL) return;

		bst* node = new bst(ic, parent);
		if (pos.compare("R") == 0) { parent->r = node; }
		if (pos.compare("L") == 0) { parent->l = node; }

		return;
	}

};

bool check_bst(bst* root, int& last){
	bool res = true;

	res = res && (root->l == NULL ? true : check_bst(root->l, last));
	if (root->v < last) res = false;
	last = root->v;
	res = res && (root->r == NULL ? true : check_bst(root->r, last));

	return res;
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
		if (check_bst(root, last)) std::cout << 1;
		else std::cout << 0;

		std::cout << std::endl;

		root = NULL;
	}
}
