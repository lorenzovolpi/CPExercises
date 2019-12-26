#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <functional>
#include <cmath>

struct segtree{
    std::vector<int64_t> tree, lazy;
    int64_t n;
    int64_t neutral;
    std::function<int64_t(int64_t, int64_t)> merge;

    segtree(int64_t n, int64_t neutral, std::function<int64_t(int64_t, int64_t)> merge) : neutral(neutral), merge(merge) {
        int64_t lim = bound2pow(n);
        this->n = lim;
        tree.assign((2*lim) - 1, neutral);
		lazy.assign((2*lim) - 1, 0);
        make_tree(0, 0, lim - 1);
    }

    segtree(int64_t n) : segtree(n, 0, default_merge) {}

    segtree(std::vector<int64_t> v, int64_t neutral, std::function<int64_t(int64_t, int64_t)> merge) : neutral(neutral), merge(merge) {
        int64_t lim = bound2pow(v.size());
        this->n = lim;
        tree.assign((2*lim) - 1, neutral);
		lazy.assign((2*lim) - 1, 0);
        for(int64_t i = lim-1; i<lim - 1 + v.size(); ++i) tree[i] = v[i - lim + 1];
        make_tree(0, 0, lim - 1);
    }

    segtree(std::vector<int64_t> v) : segtree(v, 0, default_merge) {}

    int make_tree(int64_t i, int64_t lb, int64_t rb) {
        if(lb == rb) return tree[i];
        
        int64_t mid = lb + (rb - lb + 1) / 2;
        
        int64_t mkl = make_tree(left(i), lb, mid - 1);
        int64_t mkr = make_tree(right(i), mid, rb);

        tree[i] = this->merge(mkl, mkr);

        return tree[i];
    }

    int64_t sum(int64_t kl, int64_t kr) {
        if(kl > kr) return this->neutral;
        if(kl < 0 || kr >= this->n) return this->neutral;

        return util_sum(kl, kr, 0, 0, this->n - 1);
    }

    int64_t sum(int64_t k) {
        if(k < 0 || k >= this->n) return this->neutral;
        return util_sum(0, k, 0, 0, this->n - 1);
    }

    int64_t util_sum(int64_t kl, int64_t kr, int64_t i, int64_t lb, int64_t rb) {
        util_update(i, lb, rb);
		if(kl > rb || kr < lb) return this->neutral;
        else if(kl <= lb && rb <= kr) return tree[i];
        else {
            int64_t mid = lb + (rb - lb + 1) / 2;
            return this->merge(util_sum(kl, kr, left(i), lb, mid - 1), util_sum(kl, kr, right(i), mid, rb));
        }
    }

    void add(int64_t k, int64_t v) {
        if(k < 0 || k >= this->n) return;
        util_add(k, v, 0, 0, this->n - 1);
    }

    void util_add(int64_t k, int64_t v, int64_t i, int64_t lb, int64_t rb) {
        util_update(i, lb, rb);
		if(k < lb || k > rb) return;
        else {
            tree[i] += v;
            if(lb < rb) {
                int64_t mid = lb + (rb - lb + 1) / 2;
                util_add(k, v, left(i), lb, mid - 1);
                util_add(k, v, right(i), mid, rb);
            }
        }
    }

	void util_update(int64_t i, int64_t lb, int64_t rb) {
		if(lazy[i] != 0) {
			tree[i] += lazy[i];
			if(lb < rb) {
				lazy[left(i)] += lazy[i];
				lazy[right(i)] += lazy[i];
			}
			lazy[i] = 0;
		}
	} 

	int64_t util_range_update(int64_t kl, int64_t kr, int64_t v, int64_t i, int64_t lb, int64_t rb) {
		util_update(i, lb, rb);
		if(kl <= lb && rb <= kr) {
			tree[i] += v;
			if(lb < rb) {
				lazy[left(i)] += v;
				lazy[right(i)] += v;
			}
		} else if(kl <= rb && kr >= lb) {
			int64_t mid = lb + (rb - lb + 1) / 2;
			tree[i] = this->merge(util_range_update(kl, kr, v, left(i), lb, mid - 1), util_range_update(kl, kr, v, right(i), mid, rb));
		}

		return tree[i];
	}

	void range_update(int64_t kl, int64_t kr, int64_t v) {
		if(kl > kr) return;
        if(kl < 0 || kr >= this->n) return;

		util_range_update(kl, kr, v, 0, 0, this->n - 1);
	}

    static int64_t default_merge(int64_t v1, int64_t v2) { return v1 + v2; }

    static int64_t left(int64_t i) { return i*2 + 1; }

    static int64_t right(int64_t i) { return i*2 + 2; }

    static int64_t parent(int64_t i) { return (i-1) / 2; }

    static int64_t bound2pow(int64_t n) {
        int64_t k = 0;
        while(std::pow(2, k) < n) ++k;
        return pow(2, k);
    }

};

int main()
{
	int n = 0;
	std::cin >> n;

	std::vector<int64_t> arr;
	arr.reserve(n);

	for (int i = 0; i < n; i++)
	{
		int x = 0;
		std::cin >> x;
		arr.push_back(x);
	}

	segtree st(arr, INT64_MAX, [](int64_t v1, int64_t v2) 
		{
			return std::min(v1, v2);
		});

	int q = 0;
	std::cin >> q;
	std::string s;
	std::getline(std::cin, s);
	int query[4];
	for (int i = 0; i < q; i++)
	{
		int count = 0;
		std::getline(std::cin, s);
		std::istringstream iss(s);
		while (!iss.eof())
		{
			iss >> query[count];
			count++;
		}

		if (count == 2)
		{
			int j = query[0], k = query[1];
			int res;
			if (j > k) res = std::min(st.sum(j, arr.size() - 1), st.sum(0, k));
			else res = st.sum(j, k);

			std::cout << res << std::endl;
		}
		if (count == 3)
		{
			int j = query[0], k = query[1];
			int res;
			if (j > k)
			{
				st.range_update(j, arr.size() - 1, query[2]);
				st.range_update(0, k, query[2]);
			}
			else st.range_update(j, k, query[2]);
		}
	}
}