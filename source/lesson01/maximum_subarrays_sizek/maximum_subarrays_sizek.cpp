#include <iostream>
#include <vector>
#include <climits>

void maximum_subarrays(std::vector<int> vect, int k)
{
	std::vector<int> maximums;
	maximums.reserve(vect.size() - k + 1);
	int max = INT_MIN;

	auto it = vect.begin();

	for (int i = 0; it != vect.end() && i < k; ++it, ++i) 
	{
		if (max < *it) max = *it;
	}

	maximums.push_back(max);

	for (; it != vect.end(); ++it) 
	{

	}

}

int main()
{
	int test_cases = 0;
	std::cin >> test_cases;

	std::vector<int> vect;

	for (int i = 0; i < test_cases; ++i)
	{
		int n = 0, k = 0;
		std::cin >> n;
		std::cin >> k;

		vect.reserve(n);

		for (int j = 0; j < n; ++j)
		{
			int x = 0;
			std::cin >> x;
			vect.push_back(x);
		}

		maximum_subarrays(vect, k);

		vect.clear();
	}

}