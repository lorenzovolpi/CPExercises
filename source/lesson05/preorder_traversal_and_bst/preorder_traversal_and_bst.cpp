#include <iostream>
#include <vector>
#include <climits>

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

bst* build_from_preorder(bst* root, std::vector<int> nums, int f, int l){
	if (root == NULL) root = new bst(nums[f]);

	int lf = f + 1, ll = f, rf = f + 1, rl = f;

	for (int i = lf; i <= l && nums[i] < nums[f]; i++) { ll = i; }

	rf = ll + 1;
	rl = l;

	if (lf <= ll) root->l = new bst(nums[lf], NULL, NULL, root);
	if (rf <= rl) root->r = new bst(nums[rf], NULL, NULL, root);

	if (root->l != NULL) build_from_preorder(root->l, nums, lf, ll);
	if (root->r != NULL) build_from_preorder(root->r, nums, rf, rl);

	return root;
}

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
	std::vector<int> nums;

	for (int i = 0; i < test_cases; ++i)
	{
		int n = 0;
		std::cin >> n;
		nums.reserve(n);

		for (int j = 0; j < n; ++j)
		{
			int x = 0;
			std::cin >> x;
			nums.push_back(x);
		}

		bst* root = build_from_preorder(NULL, nums, 0, nums.size() - 1);

		int last = INT_MIN;
		std::cout << (check_bst(root, last) ? 1 : 0) << std::endl;

		nums.clear();
	}
}