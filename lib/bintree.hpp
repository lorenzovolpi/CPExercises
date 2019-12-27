#ifndef __BINTREE_HPP
#define __BINTREE_HPP

#include <iostream>
#include <vector>
#include <climits>
#include <functional>

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

#endif