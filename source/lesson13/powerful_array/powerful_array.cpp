#include <iostream>
#include <vector>
#include <algorithm>

struct query
{
	int l, r, b;
	query(int l, int r, int n) : l(l), r(r) 
	{
		double _b = (double)l / sqrt(n);
		b = _b;
	}
};

int sqr(int v)
{
	return std::pow(v, 2);
}

int max(const std::vector<int>& arr)
{
	int max = INT_MIN;
	for (int i = 0; i < arr.size(); ++i) if (arr[i] > max) max = arr[i];
	return max;
}

void add(std::vector<int>& count, int& answer, int val)
{
	answer -= count[val];
	count[val] /= val;
	count[val] = std::sqrt(count[val]);
	count[val]++;
	count[val] = sqr(count[val]);
	count[val] *= val;
	answer += count[val];
}

void remove(std::vector<int>& count, int& answer, int val)
{
	answer -= count[val];
	count[val] /= val;
	count[val] = std::sqrt(count[val]);
	count[val]--;
	count[val] = sqr(count[val]);
	count[val] *= val;
	answer += count[val];
}


int main()
{
	int n, t;
	std::cin >> n;
	std::cin >> t;
	std::vector<int> arr;
	arr.reserve(n);
	for (int i = 0; i < n; ++i)
	{
		int x;
		std::cin >> x;
		arr.push_back(x);
	}

	int m = max(arr);
	std::vector<int> count(m + 1, 0);
	count[arr[0]]++;
	int answer = arr[0];

	std::vector<query> queries;
	queries.reserve(t);
	for (int i = 0; i < t; ++i)
	{
		int l, r;
		std::cin >> l;
		std::cin >> r;
		queries.emplace_back(l-1, r-1, n);
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

		std::cout << answer << std::endl;
	}

}
