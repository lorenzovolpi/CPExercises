#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>

struct query
{
	int64_t f, l, i, n = 0;

	query(int64_t first, int64_t last, int64_t index) : f(first), l(last), i(index) {};
};

struct query_bound{
    int64_t i, v;
    bool first;

    query_bound(int64_t i, int64_t v, bool first) : i(i), v(v), first(first) {}
};

template<typename T = int64_t>
struct segtree{
    std::vector<T> base, node;
    int64_t n;
    T neutral;
    std::function<T(T, T)> merge;

    segtree(int64_t n, T neutral, std::function<T(T, T)> merge) : neutral(neutral), merge(merge) {
        int64_t lim = bound2pow(n);
        this->n = lim;
        base.assign(lim, neutral);
        node.assign(lim-1, neutral);
        make_tree(0, 0, lim - 1);
    }

    segtree(int64_t n) : segtree(n, 0, default_merge) {}

    segtree(std::vector<T> v, T neutral, std::function<T(T, T)> merge) : neutral(neutral), merge(merge) {
        int64_t lim = bound2pow(v.size());
        this->n = lim;
        base.assign(lim, neutral);
        for(int64_t i = 0; i<v.size(); ++i) base[i] = v[i];
        node.assign(lim - 1, neutral);
        make_tree(0, 0, lim - 1);
    }

    segtree(std::vector<T> v) : segtree(v, 0, default_merge) {}

    int make_tree(int64_t i, int64_t lb, int64_t rb) {
        if(lb == rb) return base[lb];
        
        int64_t mid = lb + (rb - lb + 1) / 2;
        
        int64_t mkl = make_tree(left(i), lb, mid - 1);
        int64_t mkr = make_tree(right(i), mid, rb);

        node[i] = this->merge(mkl, mkr);

        return node[i];
    }

    T sum(int64_t kl, int64_t kr) {
        if(kl > kr) return this->neutral;
        if(kl < 0 || kr >= this->n) return this->neutral;

        return util_sum(kl, kr, 0, 0, this->n - 1);
    }

    T sum(int64_t k) {
        if(k < 0 || k >= this->n) return this->neutral;
        return util_sum(0, k, 0, 0, this->n - 1);
    }

    T util_sum(int64_t kl, int64_t kr, int64_t i, int64_t lb, int64_t rb) {
        if(kl > rb || kr < lb) return this->neutral;
        else if(kl <= lb && kr >= rb) {
            if(lb == rb) return base[lb];
            else return node[i];
        }
        else {
            if(lb == rb) return base[lb];
            int64_t mid = lb + (rb - lb + 1) / 2;
            return this->merge(util_sum(kl, kr, left(i), lb, mid - 1), util_sum(kl, kr, right(i), mid, rb));
        }
    }

    void add(int64_t k, T v) {
        if(k < 0 || k >= this->n) return;
        util_add(k, v, 0, 0, this->n - 1);
    }

    void util_add(int64_t k, T v, int64_t i, int64_t lb, int64_t rb) {
        if(k < lb || k > rb) return;
        else {
            if(lb == rb) base[lb] += v;
            else {
                node[i] += v;
                int64_t mid = lb + (rb - lb + 1) / 2;
                util_add(k, v, left(i), lb, mid - 1);
                util_add(k, v, right(i), mid, rb);
            }
        }
    }

    static T default_merge(T v1, T v2) { return v1 + v2; }

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
	int64_t q = 0;
	std::cin >> q;
	
    std::vector<query> qs;

	int64_t max = INT64_MIN, min = INT64_MAX;
	for (int64_t i = 0; i < q; ++i)
	{
		int64_t f, l;
		std::cin >> f;
		std::cin >> l;
		--f, --l;
		if (f < min) min = f;
		if (l > max) max = l;
		qs.emplace_back(f, l, i);
	}

    std::vector<query_bound> bounds;
    for(int i = 0; i<q; ++i) {
        bounds.emplace_back(i, qs[i].f, true);
        bounds.emplace_back(i, qs[i].l, false);
    }

    std::sort(bounds.begin(), bounds.end(), [](query_bound qb1, query_bound qb2) {
        return qb1.v < qb2.v;
    });

    for(int i = 0; i<bounds.size(); ++i) {
        if(bounds[i].first) qs[bounds[i].i].f = i;
        else qs[bounds[i].i].l = i;
    }

    std::sort(qs.begin(), qs.end(), [](query q1, query q2)
		{
			return q1.f > q2.f;
		});

    int64_t maxl = q*2 - 1;

	segtree<> st(maxl + 1);

	for (int64_t i = 0; i < q; ++i)
	{
		qs[i].n = st.sum(qs[i].l);
		st.add(qs[i].l, 1);
	}

	std::sort(qs.begin(), qs.end(), [](query q1, query q2)
		{
			return q1.i < q2.i;
		});

	for (int64_t i = 0; i < q; ++i)
	{
		std::cout << qs[i].n << std::endl;
	}
}
