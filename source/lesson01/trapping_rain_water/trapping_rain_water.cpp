#include <iostream>
#include <vector>

/*
	The idea is to parse the array from left to right with and index i and
	from right to left with an index j at the same time. The heights of the blocks 
	are compared at every iteration and the smaller is considered. If the height of blocks is smaller
	than the current level of water the difference is added to the total water trapped, 
	otherwise the level is brought to the current height. The index just considered is increased or decreased
	(i or j) until i is euqal to j. The algorithm runs in O(n).
*/

int trapped_spot(int val, int& level) 
{
	if (val > level) level = val;

	return level - val;
}

int trapping_rain_water(std::vector<int> vect)
{
	int i = 0, j = vect.size() - 1;
	int level = 0, trw = 0;

	while (i != j) 
	{
		if (vect[i] <= vect[j]) 
		{
			trw += trapped_spot(vect[i], level);
			i++;
		}

		if (vect[j] < vect[i])
		{
			trw += trapped_spot(vect[j], level);
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