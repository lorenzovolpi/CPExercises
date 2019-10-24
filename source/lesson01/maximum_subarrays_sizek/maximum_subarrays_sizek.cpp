#include <iostream>
#include <vector>
#include <deque>
#include <climits>

std::vector<int> maximum_subarrays(std::vector<int> vect, int k)
{
	std::vector<int> maximums;
	maximums.reserve(vect.size() - k + 1);
	std::deque<int> deq;

	for (int i = 0; i < vect.size(); i++) 
	{
		while (!deq.empty() && deq.front() <= (i - k)) 
		{
			deq.pop_front();
		}

		while (!deq.empty() && vect[deq.back()] <= vect[i])
		{
			deq.pop_back();
		}

		deq.push_back(i);

		if (i >= k - 1) {
			maximums.push_back(vect[deq.front()]);
		}
	}

	return maximums;
}

int main()
{
	int test_cases = 0;
	std::cin >> test_cases;

	std::vector<int> vect;

	for (int i = 0; i < test_cases; ++i)
	{
		int n = 0, k = 0;
		std::cin >> n;
		std::cin >> k;

		vect.reserve(n);

		for (int j = 0; j < n; ++j)
		{
			int x = 0;
			std::cin >> x;
			vect.push_back(x);
		}

		std::vector<int> maximums = maximum_subarrays(vect, k);

		for (auto it = maximums.begin(); it != maximums.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << "\n";

		vect.clear();
	}

}