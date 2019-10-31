#include <iostream>
#include "bst.h"

int main()
{
	int test_cases = 0;
	std::cin >> test_cases;
	std::vector<int> nums;

	for (int i = 0; i < test_cases; ++i)
	{
		int n = 0;
		std::cin >> n;
		nums.reserve(n);

		for (int j = 0; j < n; ++j)
		{
			int x = 0;
			std::cin >> x;
			nums.push_back(x);
		}

		bst* root = bst::build_from_preorder(NULL, nums, 0, nums.size() - 1);

		if (bst::check_bst(root)) std::cout << 1;
		else std::cout << 0;

		std::cout << std::endl;
		nums.clear();
	}
}