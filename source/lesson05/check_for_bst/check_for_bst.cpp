#include <iostream>
#include "bst.h"

int main()
{
	int test_cases = 0;
	std::cin >> test_cases;

	bst* root = NULL;

	for (int i = 0; i < test_cases; ++i)
	{
		int edges = 0;
		std::cin >> edges;

		for (int j = 0; j < edges; ++j)
		{
			int p = 0, c = 0;
			std::string pos = "";
			std::cin >> p;
			std::cin >> c;
			std::cin >> pos;

			root = bst::add(root, p, c, pos);
		}

		if (bst::check_bst(root)) std::cout << 1;
		else std::cout << 0;

		std::cout << std::endl;

		root = NULL;
	}
}
