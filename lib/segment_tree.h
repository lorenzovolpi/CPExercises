#ifndef SEGMENT_TREE__H
#define SEGMENT_TREE__H

#include <vector>
#include "bintree.h"

struct segment_tree : bintree
{
	int lb, ub;

	segment_tree(std::vector<int> vec);
	segment_tree(std::vector<int> vec, int lb, int ub);

	void add(int k, int val);
	int sum(int j, int k);
	int sum(int k);
};

#endif