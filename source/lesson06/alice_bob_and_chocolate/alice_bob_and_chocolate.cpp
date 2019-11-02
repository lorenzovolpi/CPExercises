#include <iostream>
#include <vector>

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