#include <iostream>
#include <vector>
#include <climits>

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