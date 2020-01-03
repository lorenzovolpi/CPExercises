#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <functional>
#include <cmath>
#include <chrono>

struct segtree{
    std::vector<int64_t> tree, lazy;
    int64_t n;
    int64_t neutral;

    segtree(int64_t n, int64_t neutral) : neutral(neutral){
        int64_t lim = bound2pow(n);
        this->n = lim;
        tree.assign((2*lim) - 1, neutral);
		lazy.assign((2*lim) - 1, 0);
        make_tree(0, 0, lim - 1);
    }

    segtree(int64_t n) : segtree(n, 0) {}

    segtree(std::vector<int64_t> v, int64_t neutral) : neutral(neutral){
        int64_t lim = bound2pow(v.size());
        this->n = lim;
        tree.assign((2*lim) - 1, neutral);
		lazy.assign((2*lim) - 1, 0);
        for(int64_t i = lim-1; i<lim - 1 + v.size(); ++i) tree[i] = v[i - lim + 1];
        make_tree(0, 0, lim - 1);
    }

    segtree(std::vector<int64_t> v) : segtree(v, 0) {}

    int make_tree(int64_t i, int64_t lb, int64_t rb) {
        if(lb == rb) return tree[i];
        
        int64_t mid = lb + (rb - lb + 1) / 2;
        
        int64_t mkl = make_tree((i << 1) + 1, lb, mid - 1);
        int64_t mkr = make_tree((i << 1) + 2, mid, rb);

        tree[i] = std::min(mkl, mkr);

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
            return std::min(util_sum(kl, kr, (i << 1) + 1, lb, mid - 1), util_sum(kl, kr, (i << 1) + 2, mid, rb));
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
                util_add(k, v, (i << 1) + 1, lb, mid - 1);
                util_add(k, v, (i << 1) + 2, mid, rb);
            }
        }
    }

	void util_update(int64_t i, int64_t lb, int64_t rb) {
		if(lazy[i] != 0) {
			tree[i] += lazy[i];
			if(lb < rb) {
				lazy[(i << 1) + 1] += lazy[i];
				lazy[(i << 1) + 2] += lazy[i];
			}
			lazy[i] = 0;
		}
	} 

	int64_t util_range_update(int64_t kl, int64_t kr, int64_t v, int64_t i, int64_t lb, int64_t rb) {
		util_update(i, lb, rb);
		if(kl <= lb && rb <= kr) {
			tree[i] += v;
			if(lb < rb) {
				lazy[(i << 1) + 1] += v;
				lazy[(i << 1) + 2] += v;
			}
		} else if(kl <= rb && kr >= lb) {
			int64_t mid = lb + (rb - lb + 1) / 2;
			tree[i] = std::min(util_range_update(kl, kr, v, (i << 1) + 1, lb, mid - 1), util_range_update(kl, kr, v, (i << 1) + 2, mid, rb));
		}

		return tree[i];
	}

	void range_update(int64_t kl, int64_t kr, int64_t v) {
		if(kl > kr) return;
        if(kl < 0 || kr >= this->n) return;

		util_range_update(kl, kr, v, 0, 0, this->n - 1);
	}

    static int64_t bound2pow(int64_t n) {
        int64_t k = 0;
        while(std::pow(2, k) < n) ++k;
        return pow(2, k);
    }

};

int main()
{
	int64_t n = 0;
	std::cin >> n;

	

	std::vector<int64_t> arr(n, 0);

	for (int64_t i = 0; i < n; i++)
	{
		int64_t x = 0;
		std::cin >> x;
		arr[i] = x;
	}

	segtree st(arr, INT64_MAX);

	int64_t q = 0;
	std::cin >> q;
	std::string s;
	std::getline(std::cin, s);
	int64_t query[4];
	for (int64_t i = 0; i < q; i++)
	{
		int64_t count = 0;
		std::getline(std::cin, s);
		std::istringstream iss(s);
		while (!iss.eof())
		{
			iss >> query[count];
			count++;
		}

		if (count == 2)
		{
			int64_t j = query[0], k = query[1];
			int64_t res;
			if (j > k) res = std::min(st.util_sum(j, arr.size() - 1, 0, 0, st.n - 1), st.util_sum(0, k, 0, 0, st.n - 1));
			else res = st.sum(j, k);

			std::cout << res << std::endl;
		}
		if (count == 3)
		{
			int64_t j = query[0], k = query[1];
			int64_t res;
			if (j > k)
			{
				st.util_range_update(j, arr.size() - 1, query[2], 0, 0, st.n - 1);
				st.util_range_update(0, k, query[2], 0, 0, st.n - 1);
			}
			else st.range_update(j, k, query[2]);
		}
	}
}