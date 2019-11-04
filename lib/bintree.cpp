#include "bintree.h"

bintree::bintree(int v) : v(v), l(NULL), r(NULL), p(NULL) {}
bintree::bintree(int v, bintree* p) : v(v), l(NULL), r(NULL), p(p) {}
bintree::bintree(int v, bintree* l, bintree* r, bintree* p) : v(v), l(l), r(r), p(p) {}

bintree* bintree::search(int value)
{

}

void bintree::add(int p, int v)
{

}

void bintree::inorder(std::function<void(bintree*)> f)
{

}

void bintree::preorder(std::function<void(bintree*)> f)
{

}

void bintree::postorder(std::function<void(bintree*)> f)
{

}
