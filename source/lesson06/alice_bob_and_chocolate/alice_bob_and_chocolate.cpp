#include <iostream>
#include <vector>

/*
	The idea is to scan the array of times from left to right and from right to left at the same
	time, simulating the process of eating bars inf each direction. At each iteration the contestant
	behind in time if brought torwards. If they are at the same time they go on together. The time
	complexity of the algorithm is O(n).
*/

int main()
{
	int n = 0;
	std::cin >> n;
	std::vector<int> vec;
	vec.reserve(n);

	for (int i = 0; i < n; ++i)
	{
		int x = 0;
		std::cin >> x;
		vec.push_back(x);
	}

	int a = -1, b = n, ta = 0, tb = 0;

	bool eaten = false;
	while (a < b && !eaten)
	{
		if (ta < tb)
		{
			if (!(eaten = a + 1 == b))
			{
				a++;
				ta += vec[a];
			}
		}
		else if (ta > tb)
		{
			if (!(eaten = a == b - 1))
			{
				b--;
				tb += vec[b];
			}
		}
		else
		{
			if (a + 1 == b - 1)
			{
				a++;
				ta += vec[a];
				eaten = true;
			}
			else if (a + 1 > b - 1)
			{
				eaten = true;
			}
			else
			{
				a++, b--;
				ta += vec[a];
				tb += vec[b];
			}
		}
	}

	std::cout << a + 1 << " " << n - b << std::endl;
}
