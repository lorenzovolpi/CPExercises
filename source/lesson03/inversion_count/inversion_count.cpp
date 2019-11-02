#include <iostream>
#include <vector>
#include "../../../lib/sort.h"


int main()
{
	int test_cases = 0;
	std::cin >> test_cases;

	std::vector<int> vec;

	for (int i = 0; i < test_cases; ++i)
	{
		int n = 0;
		std::cin >> n;
		vec.reserve(n);
		for (int j = 0; j < n; ++j)
		{
			int x = 0;
			std::cin >> x;
			vec.push_back(x);
		}
		
		int invcnt = invcnt_merge_sort(vec, 0, n-1);

		std::cout << std::endl << invcnt <<  std::endl;

		vec.clear();
	}
}