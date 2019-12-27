#include <iostream>
#include <vector>
#include <algorithm>

const int MAX_VALUE = 1000;

/*
	This solution uses an array that keeps the number of bars for
	any possible length (from 1 to 1000 as stated in the problem).
	The complexity is O(n) in time and O(n) in space (assuming that the
	maximum number of possible bars is 1000 as stated).
*/
void towers_v1(std::vector<int> vect) 
{
	std::vector<int> tows(MAX_VALUE + 1, 0);
	int num = 0, max = 0;

	for(int i = 0; i<vect.size(); ++i)
	{
		if (tows[vect[i]] == 0) num++;
		tows[vect[i]]++;
		if (tows[vect[i]] > max) max = tows[vect[i]];
	}

	std::cout << max << " " << num << std::endl;

}

/*
	This solution uses a sort-and-compute approach, bringing the complexity
	in time up to O(nlogn) and the complexity in space down to O(1);
*/
void towers_v2(std::vector<int> vect)
{
	int n = vect.size(), last = -1, currentHeight = 0, num = 0, max = 0;

	std::sort(vect.begin(), vect.end());

	for (int i = 0; i < n; ++i)
	{
		if (vect[i] != last)
		{
			last = vect[i];
			num++;
			currentHeight = 1;
		}
		else
		{
			currentHeight++;
		}

		if (currentHeight > max) max = currentHeight;
	}

	std::cout << max << " " << num << "\n";

}

int main()
{
	std::vector<int> vect;
	int n = 0;
	std::cin >> n;
	vect.reserve(n);

	for (int j = 0; j < n; ++j)
	{
		int x = 0;
		std::cin >> x;
		vect.push_back(x);
	}

	towers_v1(vect);

}