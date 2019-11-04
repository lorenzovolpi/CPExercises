#include <iostream>
#include "../../../lib/fenwick_tree.h"

int main()
{
	int test_cases = 0;
	std::cin >> test_cases;

	for (int i = 0; i < test_cases; ++i)
	{
		int n, u;
		std::cin >> n;
		std::cin >> u;

		fenwick_tree ft(n);

		for (int j = 0; j < u; ++j)
		{
			int l, r, val;
			std::cin >> l;
			std::cin >> r;
			std::cin >> val;

			ft.add(l, val);
			ft.add(r + 1, -1 * val);
		}

		int q;
		std::cin >> q;

		for (int j = 0; j < q; ++j)
		{
			int x;
			std::cin >> x;
			std::cout << "Output: " << ft.sum(x) << std::endl;
		}
	}


}