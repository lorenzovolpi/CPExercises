#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

/*
    All query bounds are compressed to minimum possible values for performance. 
    Then a bit is created and queries are sorted by decreasing starting bound. 
    For each query the sum in the bit is computed for the ending bound of the 
    query and then the bit is updated by 1 for the ending bound of the current query.
    The time complexity is O(nlogm + nlogn) where m is the number of elements of the bit.
*/

struct bit
{
	std::vector<int> v;

    bit(int n) : v(n + 1, 0) {};

    bit(int n, int val) : v(n + 1, val)
    {
        v[0] = 0;
        for (int i = 1; i <= n; ++i) 
            if((i + (i & -i)) <= n) 
                v[i + (i & -i)] += v[i]; 
    };

    bit(std::vector<int> vec) : v(vec.size() + 1)
    {
        v[0] = 0;
        for (int i = 0; i < vec.size(); ++i) { v[i + 1] = vec[i]; }
        for (int i = 1; i <= vec.size(); ++i) 
            if((i + (i & -i)) <= vec.size()) 
                v[i + (i & -i)] += v[i];
    };

    void add(int k, int val)
    {
        for (++k; k < v.size(); k += k & -k) { v[k] += val; }
    }

    int sum(int k)
    {
        int s = 0;
        for (++k; k > 0; k -= k & -k) { s += v[k]; }
        return s;
    }
};

struct query
{
	int f, l, i, n = 0;

	query(int first, int last, int index) : f(first), l(last), i(index) {};
};

struct query_bound{
    int64_t i, v;
    bool first;

    query_bound(int64_t i, int64_t v, bool first) : i(i), v(v), first(first) {}
};


int main()
{
	int q = 0;
	std::cin >> q;
	std::vector<query> qs;

	int max = INT_MIN, min = INT_MAX;
	for (int i = 0; i < q; ++i)
	{
		int f, l;
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

	bit ft(maxl + 1);

	for (int i = 0; i < q; ++i)
	{
		qs[i].n = ft.sum(qs[i].l);
		ft.add(qs[i].l, 1);
	}

	std::sort(qs.begin(), qs.end(), [](query q1, query q2)
		{
			return q1.i < q2.i;
		});

	for (int i = 0; i < q; ++i)
	{
		std::cout << qs[i].n << std::endl;
	}
}