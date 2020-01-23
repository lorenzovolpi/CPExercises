#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

/*
	For each city the distance from the center is computed. Then all cities are
	sorted by distance from the center. Then the result is computed scanning the sorted array
	until the population reaches the target. The solutions runs in o(nlogn).
*/

struct city
{
	int x, y, p;
	double d;

	city(int x, int y, int population) : x(x), y(y), p(population)
	{
		d = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
	}
};

int main()
{
	int nc, cp;

	std::cin >> nc;
	std::cin >> cp;
	std::vector<city> cities;
	cities.reserve(nc);
	for (int i = 0; i < nc; i++)
	{
		int x, y, p;
		std::cin >> x;
		std::cin >> y;
		std::cin >> p;

		cities.emplace_back(x, y, p);
	}

	std::sort(cities.begin(), cities.end(), [](city c1, city c2)
		{
			return c1.d < c2.d;
		});

	int i = 0;
	for (; i < nc && cp < 1000000; i++)
	{
		cp += cities[i].p;
	}

	if (cp >= 1000000)
	{
		std::cout.precision(8);
		std::cout << cities[i - 1].d << std::endl;
	}
	else std::cout << -1 << std::endl;
}