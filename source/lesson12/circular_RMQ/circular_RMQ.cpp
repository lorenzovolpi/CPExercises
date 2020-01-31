#include <iostream>
#include <sstream>
#include <climits>
#include <cmath>

#define MAX 200001
#define LEFT(t) (((t)*2) + 1)
#define RIGHT(t) (((t)*2) + 2)

/*
	The idea is to use a segment tree with lazy updates for range updates. Updates and
	queries are computed as usual when bounds are between starting and ending element,
	while are split in two when they overflow. The solution runs in O(n + mlogn).
*/

//source: https://github.com/Hikari9/UVa/blob/master/52C%20-%20Circular%20RMQ.cpp

int64_t vec[MAX], tree[MAX*4], lazy[MAX*4], av;
int n, upt, q, l, r;
char reads[100];

void build_tree(int ind, int lb, int rb) {
	lazy[ind] = 0;
	if(lb == rb) {
		tree[ind] = lb < n ? vec[lb] : INT64_MAX;
		return;
	}
	int mid = (lb + rb) / 2;
	build_tree(LEFT(ind), lb, mid);
	build_tree(RIGHT(ind), mid + 1, rb);
	tree[ind] = std::min(tree[LEFT(ind)], tree[RIGHT(ind)]);
}

void update(int ind, int lb, int rb) {
	if(lazy[ind]) {
		tree[ind] += lazy[ind];
		if(lb < rb) {
			lazy[LEFT(ind)] += lazy[ind];
			lazy[RIGHT(ind)] += lazy[ind];
		}
		lazy[ind] = 0;
	}
}

void range_add(int ind, int lb, int rb) {
	update(ind, lb, rb);
	if(l <= lb && rb <= r) {
		tree[ind] += av;
		if(lb < rb) {
			lazy[LEFT(ind)] += av;
			lazy[RIGHT(ind)] += av;
		}
	} else if(l <= rb && r >= lb) {
		int mid = (lb + rb) / 2;
		range_add(LEFT(ind), lb, mid);
		range_add(RIGHT(ind), mid + 1, rb);
		tree[ind] = std::min(tree[LEFT(ind)], tree[RIGHT(ind)]);
	}
}

int64_t sum(int ind, int lb, int rb) {
	update(ind, lb, rb);
	if(l > rb || r < lb) return INT64_MAX;
	else if(l <= lb && rb <= r) return tree[ind];
	else {
		int mid = (lb + rb) / 2;
		int64_t ls = sum(LEFT(ind), lb, mid);
		int64_t rs = sum(RIGHT(ind), mid + 1, rb);
		return std::min(ls, rs);
	}
}

int main() {
	std::cin >> n;
	upt = std::pow(2, std::ceil(std::log2(n)));

	for(int i = 0; i<n; ++i) std::cin >> vec[i];

	build_tree(0, 0, upt-1);

	std::cin >> q;
	std::cin.ignore();
	for(int i = 0; i<q; ++i) {
		std::cin.getline(reads, 100);
		std::istringstream iss(reads);
		iss >> l >> r;
		if(iss >> av) {
			if(l <= r) {
				range_add(0, 0, upt-1);
			} else {
				int tmp = r;
				r = n - 1;
				range_add(0, 0, upt-1);
				r = tmp;
				l = 0;
				range_add(0, 0, upt-1);
			}
		} else {
			if(l <= r) {
				std::cout << sum(0, 0, upt-1) << std::endl;
			} else {
				int tmp = r;
				r = n - 1;
				int64_t mf = sum(0, 0, upt-1);
				r = tmp;
				l = 0;
				int64_t ms = sum(0, 0, upt-1);
				std::cout << std::min(mf, ms) << std::endl;
			}
		}
	}
}
