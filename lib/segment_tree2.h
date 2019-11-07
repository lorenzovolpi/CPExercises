#ifndef SEGMENT_TREE2__H
#define SEGMENT_TREE2__H

#include <vector>
#include "bintree.h"

class segbintree : public bintree
{
public:
	int lb, ub;

	segbintree(int v, int lb, int ub);
	segbintree(int v, segbintree* p, int lb, int ub);
	segbintree(int v, segbintree* l, segbintree* r, segbintree* p, int lb, int ub);

	segbintree* getLeft();
	segbintree* getRight();
	segbintree* getParent();

	static segbintree* build(std::vector<int> vec);

	void segmentAdd(int k, int val);

	int segmentSum(int j, int k);

	using bintree::inorderTraversal;

};

struct segment_tree2 
{
	segbintree* root;

	segment_tree2(std::vector<int> vec);
	segment_tree2(int n);

	void add(int k, int val);
	int sum(int j, int k);
	int sum(int k);
	void print_leafs();
	void print();
};

#endif