#include <iostream>
#include <vector>

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
	int64_t test_cases = 0;
	std::cin >> test_cases;

	for (int64_t i = 0; i < test_cases; ++i)
	{
		int64_t n, u;
		std::cin >> n;
		std::cin >> u;

		bit ft(n);

		for (int64_t j = 0; j < u; ++j)
		{
			int64_t l, r, val;
			std::cin >> l;
			std::cin >> r;
			std::cin >> val;

			ft.add(l, val);
			ft.add(r + 1, -1 * val);
		}

		int64_t q;
		std::cin >> q;

		for (int64_t j = 0; j < q; ++j)
		{
			int64_t x;
			std::cin >> x;
			std::cout << "Output: " << ft.sum(x) << std::endl;
		}
	}


}