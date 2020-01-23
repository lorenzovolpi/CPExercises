#include <iostream>
#include <vector>
#include <deque>

/*
	The idea is to parse the array while keeping the last significant max values. At each iteration
	the indexes outside of the window are popped, then the new value encountered is added to the bottom of 
	the deque after al smaller elements are popped from the bottom. Then the current front is pushed in
	the results vector. The algorithm runs in O(n) as each element is pushed in and popped from the deque
	at most once.
*/

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