#include "bintree.h"

bintree::bintree(int v) : v(v), l(NULL), r(NULL), p(NULL) {}
bintree::bintree(int v, bintree* p) : v(v), l(NULL), r(NULL), p(p) {}
bintree::bintree(int v, bintree* l, bintree* r, bintree* p) : v(v), l(l), r(r), p(p) {}

bintree* bintree::search(int value)
{
	if (this->v == value) return this;
	
	bintree* res = NULL;
	if (this->l != NULL && (res = this->l->search(value)) != NULL) return res;
	if (this->r != NULL && (res = this->r->search(value)) != NULL) return res;
	
	return NULL;
}

void bintree::add(int p, int v, bt_side side)
{
	bintree* parent = this->search(p);

	if (parent != NULL)
	{
		bintree* c = &bintree(v, parent);
		if (side == bt_side::right) parent->r = c;
		if (side == bt_side::left) parent->l = c;
	}
}

void bintree::inorder(std::function<void(bintree*)> f)
{
	if (this->l != NULL) this->l->inorder(f);
	f(this);
	if (this->r != NULL) this->r->inorder(f);
}

void bintree::preorder(std::function<void(bintree*)> f)
{
	f(this);
	if (this->l != NULL) this->l->inorder(f);
	if (this->r != NULL) this->r->inorder(f);
}

void bintree::postorder(std::function<void(bintree*)> f)
{
	if (this->l != NULL) this->l->inorder(f);
	if (this->r != NULL) this->r->inorder(f);
	f(this);
}

bintree* bintree::build(std::vector<int> arr, int f, int l, std::function<int(int, int)> fun)
{
	if (f == l) return &bintree(arr[f]);
	
	int h = (l - f) / 2;

	bintree* lc = build(arr, f, f + h, fun);
	bintree* rc = build(arr, f + h + 1, l, fun);

	bintree* root = &bintree(fun(lc->v, rc->v), lc, rc, NULL);
	lc->p = root;
	rc->p = root;

	return root;
}

bintree* bintree::build(std::vector<int> arr, int f, int l)
{
	return bintree::build(arr, f, l, [](int a, int b) { return a + b; });
}
