#include "segment_tree.h"
#include <vector>
#include <functional>

#define LEFT(i) ((2*i)+1)
#define RIGHT(i) ((2*i)+2)
#define PARENT(i) ((i-1)/2)

void segment_tree::build(std::vector<int>& tree, int i, std::function<int(int, int)> merge)
{
	if (LEFT(i) >= tree.size()) return;
	
	int l, r;
	build(tree, LEFT(i), merge);
	build(tree, RIGHT(i), merge);
	tree[i] = merge(tree[LEFT(i)], tree[RIGHT(i)]);
}

segment_tree::segment_tree(std::vector<int> vec, int neutral, std::function<int(int,int)> merge) : neutral(neutral), merge(merge)
{
	int u = 1;
	for (; u < vec.size(); u *= 2) {}
	for (int i = vec.size(); i < u; ++i) vec.push_back(neutral);
	this->n = u;

	tree = std::vector<int>(2 * u - 1);
	for (int i = tree.size() - 1, j = u - 1; j >= 0; --i, --j) tree[i] = vec[j];

	lazy = std::vector<int>(2 * u - 1, 0);

	build(tree, 0, merge);
}

segment_tree::segment_tree(int n, int neutral, std::function<int(int, int)> merge) : neutral(neutral), merge(merge)
{
	int u = 1;
	for (; u < n; u *= 2) {}
	this->n = u;
	tree = std::vector<int>(2 * u - 1, neutral);
	lazy = std::vector<int>(2 * u - 1, 0);
}

segment_tree::segment_tree(std::vector<int> vec) : segment_tree(vec, 0, [](int v1, int v2){ return v1 + v2; }) {}

segment_tree::segment_tree(int n) : segment_tree(n, 0, [](int v1, int v2) { return v1 + v2; }) {}

void segment_tree::segment_add(int k, int val, int i, int lb, int ub)
{
	update(i);
	if (lb <= k && k <= ub)
	{
		if (lb < ub)
		{
			int h = (ub - lb) / 2;
			segment_add(k, val, LEFT(i), lb, lb + h);
			segment_add(k, val, RIGHT(i), lb + h + 1, ub);

			tree[i] = this->merge(tree[LEFT(i)], tree[RIGHT(i)]);
		}
		else tree[i] += val;
	}
}

int segment_tree::segment_sum(int j, int k, int i, int lb, int ub)
{
	update(i);
	if (j <= lb && ub <= k) return tree[i];
	else if (k < lb || ub < j) return this->neutral;
	else
	{
		int h = (ub - lb) / 2;
		return this->merge(segment_sum(j, k, LEFT(i), lb, lb + h), segment_sum(j, k, RIGHT(i), lb + h + 1, ub));
	}
}

int segment_tree::segment_update_range(int j, int k, int val, int i, int lb, int ub)
{
	update(i);
	if (j <= lb && ub <= k)
	{
		tree[i] += val;
		if (LEFT(i) < tree.size())
		{
			lazy[LEFT(i)] += val;
			lazy[RIGHT(i)] += val;
		}
	}
	else if (k >= lb && j <= ub) 
	{
		int h = (ub - lb) / 2;
		tree[i] = this->merge(segment_update_range(j, k, val, LEFT(i), lb, lb + h), segment_update_range(j, k, val, RIGHT(i), lb + h + 1, ub));
	}

	return tree[i];
}

void segment_tree::update(int i)
{
	if (lazy[i] != 0)
	{
		tree[i] += lazy[i];
		if (LEFT(i) < tree.size())
		{
			lazy[LEFT(i)] += lazy[i];
			lazy[RIGHT(i)] += lazy[i];
		}
		lazy[i] = 0;
	}
}

void segment_tree::add(int k, int val)
{
	segment_add(k, val, 0, 0, this->n - 1);
}

int segment_tree::sum(int j, int k)
{
	return (j <= k) ? segment_sum(j, k, 0, 0, this->n - 1) : this->neutral;
}

int segment_tree::sum(int k)
{
	return sum(0, k);
}

void segment_tree::range_update(int j, int k, int val)
{
	if(j <= k) segment_update_range(j, k, val, 0, 0, this->n - 1);
}
