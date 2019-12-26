#include <iostream>
#include <vector>
#include <algorithm>

struct pair{
	int a, b;

	pair(int a, int b) : a(a), b(b) {}
};

int main()
{
	int n, k;
	std::cin >> n;
	std::cin >> k;
	std::vector<int> arr;
	arr.reserve(n);

	for (int i = 0; i < n; i++)
	{
		int x = 0;
		std::cin >> x;
		arr.push_back(x);
	}

	std::vector<pair> ps;
	for(int i = 0; i<n; ++i) {
		for(int j = 0; j<n; ++j) {
			ps.emplace_back(arr[i], arr[j]);
		}
	}

	std::sort(ps.begin(), ps.end(), [](pair p1, pair p2) {
		return p1.a == p2.a ? p1.b < p2.b : p1.a < p2.a;
	});

	--k;

	std::cout << ps[k].a << " " << ps[k].b << std::endl;
}