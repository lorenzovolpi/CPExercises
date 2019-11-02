#include <iostream>
#include <vector>
#include <algorithm>

struct cube
{
	int i, v, h;

	cube(int index, int value) : i(index), v(value), h(1){}
};

int main()
{
	int n = 0;
	std::cin >> n;
	std::vector<cube> arr;
	arr.reserve(2 * n);

	for (int i = 0; i < 2 * n; i++)
	{
		int x;
		std::cin >> x;
		arr.emplace_back(i, x);
	}

	std::sort(arr.begin(), arr.end(), [](cube c1, cube c2)
		{
			return c1.v > c2.v;
		});

	std::vector<cube> h1, h2;
	h1.reserve(n);
	h2.reserve(n);
	for (int i = 0; i < 2 * n; i++)
	{
		int h = (i % 2) + 1;
		arr[i].h = h;

		if (h == 1) h1.push_back(arr[i]);
		else h2.push_back(arr[i]);
	}

	int c1 = 1, c2 = 1;
	for (int i = 0; i < n; i++)
	{
		if (i > 0 && h1[i].v != h1[i - 1].v) c1++;
		if (i > 0 && h2[i].v != h2[i - 1].v) c2++;
	}

	std::cout << c1 * c2 << std::endl;

	std::sort(arr.begin(), arr.end(), [](cube c1, cube c2)
		{
			return c1.i < c2.i;
		});

	for (int i = 0; i < 2 * n; i++) std::cout << arr[i].h << " "; 
	std::cout << std::endl;
}