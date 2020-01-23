#include <iostream>
#include <vector>
#include <algorithm>

/*
	The idea to find the kth pair starts sorting the array. Then the first element of the pair is
	computed using integral division btween k and n (the number of elements). The element at position
	k/n is the first element of the pair (r1). Next two other values are computed: the number of elements
	less then r1 and the number of elements equal to r1. Now we compute k' = k - before * n. The following pairs
	are repeated eq times each, so to find r2 we want the element at position k'/eq. The cost is O(n).
*/
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