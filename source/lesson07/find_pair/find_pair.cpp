#include <iostream>
#include <vector>
#include <algorithm>


int main()
{
	int64_t n, k;
	std::cin >> n;
	std::cin >> k;
	std::vector<int64_t> arr;
	arr.reserve(n);

	for (int64_t i = 0; i < n; i++)
	{
		int64_t x = 0;
		std::cin >> x;
		arr.push_back(x);
	}

	std::sort(arr.begin(), arr.end(), [](int64_t a, int64_t b) { return a < b; });

	--k;
	int64_t r1 = arr[k / n];
	int64_t before = 0;
	for(int64_t i = 0; i<n; ++i) {
		if(arr[i] < r1) before++;
		else break;
	}

	int64_t eq = 0;
	for(int64_t i = 0; i<n; ++i) {
		if(arr[i] == r1) eq++;
		else if(arr[i] > r1) break;
	}

	int64_t r2 = arr[(k - before * n) / eq];

	std::cout << r1 << " " << r2 << std::endl;
}