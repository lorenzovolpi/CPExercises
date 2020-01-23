#include <iostream>
#include <vector>
#include <climits>

/*
	This solution parses the array from left to right. I sums the subarray until the sum is negative. If the sum
	becomes negative the sum starts over, because the preceding subarray of the optimal subarray must be of negative
	sum, otherwise the optimal subarray coul be extended. The algorithm runs in O(n).
*/

int kadanes_algorithm(std::vector<int> vect) 
{
	int sum = 0, max = INT_MIN;

	for(auto it = vect.begin(); it != vect.end(); ++it)
	{
		if (sum > 0) sum += *it;
		else sum = *it;

		if (sum > max) max = sum;
	}

	return max;
}


int main()
{
	int test_cases = 0;
	std::cin >> test_cases;

	std::vector<int> vect;

	for (int i = 0; i < test_cases; ++i) 
	{
		int n = 0;
		std::cin >> n;
		vect.reserve(n);

		for (int j = 0; j < n; ++j)
		{
			int x = 0;
			std::cin >> x;
			vect.push_back(x);
		}

		int max_sum = kadanes_algorithm(vect);
		std::cout << max_sum << "\n";

		vect.clear();
	}
}