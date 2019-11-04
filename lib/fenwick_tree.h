#ifndef FENWICK_TREE__H
#define FENWICK_TREE__H

#include <vector>

struct fenwick_tree
{
	std::vector<int> v;

	fenwick_tree(int n);
	fenwick_tree(int n, int val);
	fenwick_tree(std::vector<int> vec);

	void add(int k, int val);
	int sum(int k);
};

#endif