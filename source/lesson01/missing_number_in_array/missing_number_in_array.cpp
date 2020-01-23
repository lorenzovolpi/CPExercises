#include <iostream>
#include <vector>

/*
	This solution simply sums all the elements in the array of length n-1. 
	The sums of the numbers from 1 to n minus the sum got above gives the
	missing number. The algorithm runs in O(n).
*/

int missing_number(std::vector<int> vect)
{
	int n = vect.size() + 1; 
	int n_sum = n * (n + 1) / 2;
	int sum = 0;

	for (auto it = vect.begin(); it != vect.end(); ++it)
	{
		sum += *it;
	}

	return n_sum - sum;
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

		for (int j = 0; j < n-1; ++j)
		{
			int x = 0;
			std::cin >> x;
			vect.push_back(x);
		}

		int miss = missing_number(vect);
		std::cout << miss << "\n";

		vect.clear();
	}
}