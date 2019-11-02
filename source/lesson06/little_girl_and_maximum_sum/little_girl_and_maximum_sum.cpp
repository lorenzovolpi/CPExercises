#include <iostream>
#include <vector>
#include <algorithm>

struct query
{
	int s, e;
	query(int start, int end) : s(start), e(end) {};
};

struct freq
{
	int i, v;
	freq(int index, int value) : i(index), v(value) {};
};

void prefix_sum(std::vector<freq>& f)
{
	for (int i = 1; i < f.size(); i++) f[i].v += f[i - 1].v; 
}

void prefix_sum(std::vector<int>& f)
{
	for (int i = 1; i < f.size(); i++) f[i] += f[i - 1];
}

int main()
{
	int n, q;
	std::cin >> n;
	std::cin >> q;
	std::vector<int> arr;
	std::vector<freq> freqs;
	arr.reserve(n);
	freqs.reserve(n);
	std::vector<query> queries;
	queries.reserve(q);

	for (int i = 0; i < n; i++)
	{
		int x;
		std::cin >> x;
		arr.push_back(x);
		freqs.emplace_back(i, 0);
	}

	for (int i = 0; i < q; i++)
	{
		int s, e;
		std::cin >> s;
		std::cin >> e;
		queries.emplace_back(s - 1, e - 1);
		freqs[s - 1].v += 1;
		if (e < n) freqs[e].v -= 1;
	}

	prefix_sum(freqs);

	std::sort(arr.begin(), arr.end(), [](int i1, int i2) 
		{
			return i1 > i2;
		});
	std::sort(freqs.begin(), freqs.end(), [](freq& f1, freq& f2)
		{
			return f1.v > f2.v;
		});

	std::vector<int> rarr(arr);
	
	for (int i = 0; i < n; i++) rarr[freqs[i].i] = arr[i];

	prefix_sum(rarr);

	int sum = 0;
	for (int i = 0; i < q; i++)
	{
		sum += rarr[queries[i].e] - (queries[i].s - 1 < 0 ? 0 : rarr[queries[i].s - 1]);
	}

	std::cout << sum << std::endl;
}