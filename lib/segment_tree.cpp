#include "segment_tree.h"
#include <vector>

segment_tree::segment_tree(std::vector<int> vec, int lb, int ub) : p(NULL), lb(lb), ub(ub)
{
	if (lb == ub)
	{
		this->v = vec[lb];
		this->l = this->r = NULL;
	}
	else
	{
		int h = (ub - lb) / 2;
		this->l = &segment_tree(vec, lb, lb + h);
		this->r = &segment_tree(vec, lb + h + 1, ub);
		this->l->p = this;
		this->r->p = this;
		this->v = this->r->v + this->l->v;
	}
}

segment_tree::segment_tree(std::vector<int> vec)
{
	int ub = 1;
	for (; ub < vec.size() + 1 && vec.size() > 0; ub *= 2) {}
	for (int i = vec.size(); i < ub; ++i) { vec.push_back(0); }
	this(vec, 0, ub - 1);
};

void segment_tree::add(int k, int val)
{
	if (this->lb <= k && k <= this->ub)
	{
		this->v += val;
		if (this->lb < this->ub)
		{
			((segment_tree*)(this->l))->add(k, val);
			((segment_tree*)(this->r))->add(k, val);
		}
	}
}

int segment_tree::sum(int j, int k)
{
	if (j <= this->lb && this->ub <= k) return this->v;
	else if (k < this->lb || this->ub < j) return 0;
	else 
	{
		return ((segment_tree*)(this->l))->sum(j, k) + ((segment_tree*)(this->r))->sum(j, k);
	}
}

int segment_tree::sum(int k)
{
	return this->sum(0, k);
}

