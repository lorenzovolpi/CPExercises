#include <iostream>
#include "../../../lib/BinaryTree.h"

int main()
{
	int test_cases = 0;
	std::cin >> test_cases;

	for (int i = 0; i < test_cases; ++i)
	{
		int n = 0;
		std::cin >> n;
		BinaryTree* root = NULL;
		for (int j = 0; j < n; ++j)
		{
			int ip, ic;
			std::string pos;

			std::cin >> ip;
			std::cin >> ic;
			std::cin >> pos;

			if (root == NULL) root = new BinaryTree(ip);

			root->add(ip, ic, pos);
		}

		int mtl = 0, mps = 0;

		mps = root->maxPathSum(mtl);

		std::cout << mps << std::endl;
	}
}