#include <iostream>
#include <vector>
#include <algorithm>
#include "../../../lib/segment_tree.h"

struct query
{
	int f, l, i, n = 0;

	query(int first, int last, int index) : f(first), l(last), i(index) {};
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

	int delta = 0;
	if (min < 0) delta = 0 - min;

	std::sort(qs.begin(), qs.end(), [](query q1, query q2)
		{
			return q1.f > q2.f;
		});

	segment_tree st(max + delta + 1);

	for (int i = 0; i < q; ++i)
	{
		qs[i].n = st.sum(qs[i].l + delta);
		st.add(qs[i].l + delta, 1);
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
