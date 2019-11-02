#include <iostream>
#include <vector>
#include <algorithm>

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

	std::sort(arr.begin(), arr.end());

	--k;
	int p1 = arr[k / n], p2 = arr[k % n];

	std::cout << p1 << " " << p2 << std::endl;
}