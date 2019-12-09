#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "../../../lib/segment_tree.h"

int main()
{
	int n = 0;
	std::cin >> n;

	std::vector<int> arr;
	arr.reserve(n);

	for (int i = 0; i < n; i++)
	{
		int x = 0;
		std::cin >> x;
		arr.push_back(x);
	}

	segment_tree st(arr, INT_MAX, [](int v1, int v2) 
		{
			return std::min(v1, v2);
		});

	int q = 0;
	std::cin >> q;
	std::string s;
	std::getline(std::cin, s);
	int query[4];
	for (int i = 0; i < q; i++)
	{
		int count = 0;
		std::getline(std::cin, s);
		std::istringstream iss(s);
		while (!iss.eof())
		{
			iss >> query[count];
			count++;
		}

		if (count == 2)
		{
			int j = query[0], k = query[1];
			int res;
			if (j > k) res = std::min(st.sum(j, arr.size() - 1), st.sum(0, k));
			else res = st.sum(j, k);

			std::cout << res << std::endl;
		}
		if (count == 3)
		{
			int j = query[0], k = query[1];
			int res;
			if (j > k)
			{
				st.range_update(j, arr.size() - 1, query[2]);
				st.range_update(0, k, query[2]);
			}
			else st.range_update(j, k, query[2]);
		}
	}
}