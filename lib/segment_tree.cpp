#include "segment_tree.h"
#include <vector>

segbintree::segbintree(int v, int lb, int ub) : bintree(v), lb(lb), ub(ub) {}

segbintree::segbintree(int v, segbintree* p, int lb, int ub) : bintree(v, p), lb(lb), ub(ub) {}

segbintree::segbintree(int v, segbintree* l, segbintree *r, segbintree *p, int lb, int ub) : bintree(v, l, r, p), lb(lb), ub(ub) {}

segbintree* segbintree::getLeft()
{
	return (segbintree*)this->bintree::getLeft();
}

segbintree* segbintree::getRight()
{
	return (segbintree*)this->bintree::getRight();
}

segbintree* segbintree::getParent()
{
	return (segbintree*)this->bintree::getParent();
}

segbintree* segbintree::build(std::vector<int> vec)
{
	std::vector<segbintree*> segs;
	for (int i = 0; i < vec.size(); ++i)
	{
		segs.push_back(new segbintree(vec[i], i, i));
	}

	int n = vec.size();
	for (int k = n >> 1; k > 0; k = k >> 1)
	{
		for (int i = 0; i < vec.size(); i += n / k)
		{
			segbintree *l = segs[i], *r = segs[i + ((n / k) / 2)];
			segbintree *p = new segbintree(l->getValue() + r->getValue(), l, r, NULL, i, i + (n / k) - 1);
			l->setParent(p);
			r->setParent(p);
			segs[i] = p;
		}
	}

	return segs[0];
}

void segbintree::segmentAdd(int k, int val)
{
	if (this->lb <= k && k <= this->ub)
	{
		this->setValue(this->getValue() + val);
		if (this->lb < this->ub)
		{
			this->getLeft()->segmentAdd(k, val);
			this->getRight()->segmentAdd(k, val);
		}
	}
}

int segbintree::segmentSum(int j, int k)
{
	if (j <= this->lb && this->ub <= k) return this->getValue();
	else if (k < this->lb || this->ub < j) return 0;
	else
	{
		this->getLeft()->segmentSum(j, k) + this->getRight()->segmentSum(j, k);
	}
}

segment_tree::segment_tree(std::vector<int> vec) 
{
	int u = 1;
	for (; u < vec.size(); u *= 2) {}
	for (int i = vec.size(); i < u; ++i) vec.push_back(0);
	root = segbintree::build(vec);
}

segment_tree::segment_tree(int n)
{
	int u = 1;
	for (; u < n; u *= 2) {}
	std::vector<int> vec(u, 0);
	root = segbintree::build(vec);
}

void segment_tree::add(int k, int val)
{
	this->root->segmentAdd(k, val);
}

int segment_tree::sum(int j, int k)
{
	return this->root->segmentSum(j, k);
}

int segment_tree::sum(int k)
{
	return this->root->segmentSum(0, k);
}

void segment_tree::print_leafs()
{
}

void segment_tree::print()
{
	this->root->inorderTraversal([](bintree* r)
		{
			std::cout << r->getValue() << " ";
		});

}
