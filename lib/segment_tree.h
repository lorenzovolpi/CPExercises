#ifndef SEGMENT_TREE__H
#define SEGMENT_TREE__H

#include <vector>
#include <functional>

struct segment_tree
{
private:
	void segment_add(int k, int val, int i, int lb, int ub);
	int segment_sum(int j, int k, int i, int lb, int ub);
	int segment_update_range(int j, int k, int val, int i, int lb, int ub);
	void update(int i);
public:
	std::vector<int> tree, lazy;
	int neutral, n;
	std::function<int(int, int)> merge;

	segment_tree(std::vector<int> vec, int neutral, std::function<int(int, int)> merge);
	segment_tree(int n, int neutral, std::function<int(int, int)> merge);
	segment_tree(std::vector<int> vec);
	segment_tree(int n);

	static void build(std::vector<int>& tree, int i, std::function<int(int, int)> merge);

	void add(int k, int val);
	int sum(int j, int k);
	int sum(int k);
	void range_update(int j, int k, int val);
};

#endif