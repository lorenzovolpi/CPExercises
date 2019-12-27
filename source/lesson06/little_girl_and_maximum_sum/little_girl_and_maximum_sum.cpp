#include <iostream>
#include <vector>
#include <algorithm>

struct query
{
	int64_t s, e;
	query(int64_t start, int64_t end) : s(start), e(end) {};
};

struct freq
{
	int64_t i, v;
	freq(int64_t index, int64_t value) : i(index), v(value) {};
};

void prefix_sum(std::vector<freq>& f)
{
	for (int64_t i = 1; i < f.size(); i++) f[i].v += f[i - 1].v; 
}

void prefix_sum(std::vector<int64_t>& f)
{
	for (int64_t i = 1; i < f.size(); i++) f[i] += f[i - 1];
}

int main()
{
	int64_t n, q;
	std::cin >> n;
	std::cin >> q;
	std::vector<int64_t> arr;
	std::vector<freq> freqs;
	arr.reserve(n);
	freqs.reserve(n);
	std::vector<query> queries;
	queries.reserve(q);

	for (int64_t i = 0; i < n; i++)
	{
		int64_t x;
		std::cin >> x;
		arr.push_back(x);
		freqs.emplace_back(i, 0);
	}

	for (int64_t i = 0; i < q; i++)
	{
		int64_t s, e;
		std::cin >> s;
		std::cin >> e;
		queries.emplace_back(s - 1, e - 1);
		freqs[s - 1].v += 1;
		if (e < n) freqs[e].v -= 1;
	}

	prefix_sum(freqs);

	std::sort(arr.begin(), arr.end(), [](int64_t i1, int64_t i2) 
		{
			return i1 > i2;
		});
	std::sort(freqs.begin(), freqs.end(), [](freq& f1, freq& f2)
		{
			return f1.v > f2.v;
		});

	std::vector<int64_t> rarr(arr);
	
	for (int64_t i = 0; i < n; i++) rarr[freqs[i].i] = arr[i];

	prefix_sum(rarr);

	int64_t sum = 0;
	for (int64_t i = 0; i < q; i++)
	{
		sum += rarr[queries[i].e] - (queries[i].s - 1 < 0 ? 0 : rarr[queries[i].s - 1]);
	}

	std::cout << sum << std::endl;
}