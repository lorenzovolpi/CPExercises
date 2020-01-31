#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

/*
	The algorithm is an application of Mo's algorithm. An array count
	stores the number of occurrences of elements in a given subarray
	of the original one and answer stores the sum of the requires function
	applied to all the values of count.
*/


struct query
{
	int l, r, b, i = 0;
	query(int l, int r, int n, int i) : l(l), r(r), i(i) 
	{
		double _b = (double)l / sqrt(n);
		b = (int)_b;
	}
};

int64_t sqr(int v)
{
	return std::pow(v, 2);
}

int max(const std::vector<int>& arr)
{
	int max = 0;
	for (int i = 0; i < arr.size(); ++i) if (arr[i] > max) max = arr[i];
	return max;
}

void add(std::vector<int>& count, int64_t& answer, int val)
{
	answer -= (int64_t)(sqr(count[val]) * (int64_t)val);
	count[val]++;
	answer += (int64_t)(sqr(count[val]) * (int64_t)val);
}

void remove(std::vector<int>& count, int64_t& answer, int val)
{
	answer -= (int64_t)(sqr(count[val]) * (int64_t)val);
	count[val]--;
	answer += (int64_t)(sqr(count[val]) * (int64_t)val);
}

int main()
{
	int n, t;
	std::cin >> n;
	std::cin >> t;
	std::vector<int> arr(n, 0);
	std::vector<int64_t> answ(n, 0);
	arr.reserve(n);
	for (int i = 0; i < n; ++i)
	{
		int x;
		std::cin >> x;
		arr[i] = x;
	}

	int m = max(arr);
	std::vector<int> count(m + 1, 0);
	count[arr[0]] += 1;
	int64_t answer = arr[0];

	std::vector<query> queries;
	queries.reserve(t);
	for (int i = 0; i < t; ++i)
	{
		int l, r;
		std::cin >> l;
		std::cin >> r;
		queries.emplace_back(l-1, r-1, n, i);
	}

	std::sort(queries.begin(), queries.end(), [](query q1, query q2)
		{
			return q1.b == q2.b ? q1.r < q2.r : q1.b < q2.b;
		});

	int cl = 0, cr = 0;
	for (int i = 0; i < t; ++i)
	{
		while (cr < queries[i].r)
		{
			cr++;
			add(count, answer, arr[cr]);
		}

		while (cr > queries[i].r)
		{
			remove(count, answer, arr[cr]);
			cr--;
		}

		while (cl < queries[i].l)
		{
			remove(count, answer, arr[cl]);
			cl++;
		}

		while (cl > queries[i].l)
		{
			cl--;
			add(count, answer, arr[cl]);
		}

		answ[queries[i].i] = answer;
	}

	for(int i = 0; i<t; ++i) std::cout << answ[i] << std::endl;
}
