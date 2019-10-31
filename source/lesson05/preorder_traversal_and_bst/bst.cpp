#include "bst.h"

//bst::private

void bst::set_left(bst* left) { this->l = left; }

void bst::set_right(bst* right) { this->r = right; }

void bst::set_parent(bst* parent) { this->p = parent; }

bool bst::rec_check_bst(bst* root, int& last)
{
	if (root == NULL) return true;

	bool res = true;

	res = res & rec_check_bst(root->l, last);
	if (root->v < last) res = false;
	last = root->v;
	res = res & rec_check_bst(root->r, last);

	return res;
}

//bst::public

bst::bst() : 
	v(0), l(NULL), r(NULL), p(NULL) 
{}

bst::bst(int value) :
	v(value), l(NULL), r(NULL), p(NULL)
{}

bst::bst(int value, bst* left, bst* right, bst* parent) : 
	v(value), l(left), r(right), p(parent) 
{}

bst* bst::search(bst* root, int value)
{
	if (root == NULL) return NULL;

	if (root->v == value) return root;
	if (value < root->v) return search(root->l, value);
	if (value > root->v) return search(root->r, value);
}

bst* bst::add(bst* root, int ip, int ic, const std::string &pos)
{
	bst* parent = bst::search(root, ip);

	if (parent == NULL)
	{
		root = new bst(ip);
		parent = root;
	}

	bst* node = new bst(ic, NULL, NULL, parent);
	if (pos.compare("R") == 0) { parent->set_right(node); }
	if (pos.compare("L") == 0) { parent->set_left(node); }

	return root;
}

bst* bst::add(bst* root, bst* child)
{
	if (root == NULL) root = child;

	if (child->v > root->v)
	{
		if (root->r == NULL)
		{
			root->r = child;
			child->p = root;
		}
		else
		{
			bst::add(root->r, child);
		}
	}

	if (child->v < root->v)
	{
		if (root->l == NULL)
		{
			root->l = child;
			child->p = root;
		}
		else 
		{
			bst::add(root->l, child);
		}
	}

	return root;
}

bool bst::check_bst(bst* root)
{
	int last = INT_MIN;
	return rec_check_bst(root, last);
}

bst* bst::build_from_preorder(bst* root, std::vector<int> nums, int f, int l)
{
	if (root == NULL) root = new bst(nums[f]);

	int lf = f + 1, ll = f, rf = f + 1, rl = f;

	for (int i = lf; i <= l && nums[i] < nums[f]; i++) { ll = i; }

	rf = ll + 1;
	rl = l;

	if (lf <= ll) root->l = new bst(nums[lf], NULL, NULL, root);
	if (rf <= rl) root->r = new bst(nums[rf], NULL, NULL, root);

	if (root->l != NULL) bst::build_from_preorder(root->l, nums, lf, ll);
	if (root->r != NULL) bst::build_from_preorder(root->r, nums, rf, rl);

	return root;
}
