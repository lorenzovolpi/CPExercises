#include <iostream>
#include <vector>
#include <algorithm>
#include "../../../lib/fenwick_tree.h"

struct sorter
{
	int i, v, r=0;
	sorter(int index, int value) : i(index), v(value) {}
};

int main()
{
	int n = 0;
	std::cin >> n;

	std::vector<int> arr(n, 0);
	std::vector<sorter> s;
	s.reserve(n);

	for (int i = 0; i < n; ++i)
	{
		int x; 
		std::cin >> x;
		s.emplace_back(i, x);
	}

	std::sort(s.begin(), s.end(), [](sorter s1, sorter s2)
		{
			return s1.v < s2.v;
		});

	for (int i = 0; i < n; ++i)
	{
		if ((i != 0 && s[i].v != s[i - 1].v) || i == 0) { s[i].r = i; }
		else { s[i].r = s[i - 1].r; }

		arr[s[i].i] = s[i].r;
	}

	std::vector<int> occ(n, 0), suffc(n, 0);

	for (int i = n - 1; i >= 0; --i) { suffc[i] = ++occ[arr[i]]; }

	fenwick_tree b(n);

	for (int i = 0; i < n; ++i) { b.add(suffc[i], 1); }

	int sum = 0;
	for (int i = 0; i < n; ++i) occ[i] = 0;
	for (int i = 0; i < n; ++i)
	{
		b.add(suffc[i], -1);
		int k = ++occ[arr[i]];
		sum += b.sum(k - 1);
	}

	std::cout << sum << std::endl;
}