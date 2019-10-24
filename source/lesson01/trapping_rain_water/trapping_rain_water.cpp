#include <iostream>
#include <vector>

int trapping_rain_water(std::vector<int> vect)
{
	int i = 0, j = vect.size() - 1;
	int level = 0, trw = 0;

	while (i != j) 
	{
		if (vect[i] <= vect[j]) 
		{
			if (vect[i] > level) level = vect[i];

			trw += level - vect[i];
			i++;
		}

		if (vect[j] < vect[i])
		{
			if (vect[j] > level) level = vect[j];

			trw += level - vect[j];
			j--;
		}
	}

	return trw;
}

int main()
{
	int test_cases = 0;
	std::cin >> test_cases;

	std::vector<int> vect;

	for (int i = 0; i < test_cases; ++i)
	{
		int n = 0;
		std::cin >> n;
		vect.reserve(n);

		for (int j = 0; j < n; ++j)
		{
			int x = 0;
			std::cin >> x;
			vect.push_back(x);
		}

		int trw = trapping_rain_water(vect);

		std::cout << trw << "\n";

		vect.clear();
	}
}