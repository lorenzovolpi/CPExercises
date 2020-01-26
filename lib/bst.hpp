#ifndef __BST_HPP
#define __BST_HPP

#include <string>

struct bst
{
	int v;
	bst *l, *r, *p;

	bst(int value) : v(value), l(nullptr), r(nullptr), p(nullptr) {}
	bst(int value, bst* parent) : v(value), l(nullptr), r(nullptr), p(parent) {}
	bst(int value, bst* left, bst* right, bst* parent) : v(value), l(left), r(right), p(parent) {}

	bst* bsearch(int value){
		if (this->v == value) return this;
		if (value < this->v)
		{
			if (this->l == nullptr) return nullptr;
			else this->l->bsearch(value);
		}
		if (value > this->v)
		{
			if (this->r == nullptr) return nullptr;
			else return this->r->bsearch(value);
		}
	}

	bst* search(int value) {
		if (this->v == value) return this;
		bst* res = this->l == nullptr ? nullptr : this->l->search(value);
		if(res == nullptr) res = this->r == nullptr ? nullptr : this-> r->search(value);
		return res;
	}
	
	void add(bst* child) {
		if (child->v > this->v)
		{
			if (this->r == nullptr)
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
			if (this->l == nullptr)
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

		if (parent == nullptr) return;

		bst* node = new bst(ic, parent);
		if (pos.compare("R") == 0) { parent->r = node; }
		if (pos.compare("L") == 0) { parent->l = node; }

		return;
	}

};

#endif



