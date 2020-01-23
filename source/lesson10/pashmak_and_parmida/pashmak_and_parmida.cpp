#include <iostream>
#include <vector>
#include <algorithm>

/*
	The algorithm starts normalizing the values of the original array. Then two new arrays are 
	computed: occ and suffc. Each index of occ corresponds to an element of arr and occ[arr[i]] 
	stores the number of occurrences of arr[i] in arr. While computing occ, suffc is computed, 
	scanning the array backwards. suffc[i] stores the number of occurrences of arr[i] in the 
	suffix of arr starting at position i. In other words, for each i suffc stores the value of 
	the function f(i, n, ai). Then a BIT is populated. For each index i from 0 to n-1 an add 
	operation is performed on the BIT at index suffc[i] with value 1. In other words the BIT 
	stores the prefix sum of the possible suffc values. Now, scanning the array in natural 
	order, we compute for each index i the number of elements in the prefix ending with i
	which are equal to ai, keeping an ord array as before. So, at each step we compute the
	function f(1, i, ai). Now we need the number of suffixes with a value less than f(1, i, ai)
	starting after i. To have this value at each step we decrease the value of the position 
	suffc[i] in the BIT by 1 and then we compute BIT.sum(f(1, i, ai) - 1). The algorithm
	runs in O(nlogn).
*/

struct sorter
{
	int64_t i, v, r=0;
	sorter(int64_t index, int64_t value) : i(index), v(value) {}
};

struct bit
{
	std::vector<int64_t> v;

    bit(int64_t n) : v(n + 1, 0) {};

    bit(int64_t n, int64_t val) : v(n + 1, val)
    {
        v[0] = 0;
        for (int64_t i = 0; (i + (i & -1)) <= n; ++i) { v[i + (i & -i)] += v[i]; }
    };

    bit(std::vector<int64_t> vec) : v(vec.size() + 1)
    {
        v[0] = 0;
        for (int64_t i = 0; i < vec.size(); ++i) { v[i + 1] = vec[i]; }
        for (int64_t i = 1; (i + (i & -i)) <= vec.size(); ++i) { v[i + (i & -i)] += v[i]; }
    };

    void add(int64_t k, int64_t val)
    {
        for (++k; k < v.size(); k += k & -k) { v[k] += val; }
    }

    int64_t sum(int64_t k)
    {
        int64_t s = 0;
        for (++k; k > 0; k -= k & -k) { s += v[k]; }
        return s;
    }
};

int main()
{
	int64_t n = 0;
	std::cin >> n;

	std::vector<int64_t> arr(n, 0);
	std::vector<sorter> s;
	s.reserve(n);

	for (int64_t i = 0; i < n; ++i)
	{
		int64_t x; 
		std::cin >> x;
		s.emplace_back(i, x);
	}

	std::sort(s.begin(), s.end(), [](sorter s1, sorter s2)
		{
			return s1.v < s2.v;
		});

	for (int64_t i = 0; i < n; ++i)
	{
		if ((i != 0 && s[i].v != s[i - 1].v) || i == 0) { s[i].r = i; }
		else { s[i].r = s[i - 1].r; }

		arr[s[i].i] = s[i].r;
	}

	std::vector<int64_t> occ(n, 0), suffc(n, 0);

	for (int64_t i = n - 1; i >= 0; --i) { suffc[i] = ++occ[arr[i]]; }

	bit b(n);

	for (int64_t i = 0; i < n; ++i) { b.add(suffc[i], 1); }

	int64_t sum = 0;
	for (int64_t i = 0; i < n; ++i) occ[i] = 0;
	for (int64_t i = 0; i < n; ++i)
	{
		b.add(suffc[i], -1);
		int64_t k = ++occ[arr[i]];
		sum += b.sum(k - 1);
	}

	std::cout << sum << std::endl;
}