#ifndef BINTREE__H
#define BINTREE_H

#include <iostream>
#include <functional>

struct bintree
{
	bintree *l, *r, *p;
	int v;

	bintree(int v);
	bintree(int v, bintree* p);
	bintree(int v, bintree* l, bintree* r, bintree* p);

	bintree* search(int value);
	
	void add(int p, int v);
	
	void inorder(std::function<void(bintree*)> f);
	void preorder(std::function<void(bintree*)> f);
	void postorder(std::function<void(bintree*)> f);
};


#endif // !BINTREE__H
