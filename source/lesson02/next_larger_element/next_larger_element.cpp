#include <iostream>
#include <vector>
#include <deque>

std::vector<int64_t> next_larger_element(std::vector<int64_t> vect)
{
	std::deque<int64_t> deq;
	std::vector<int64_t> nle(vect.size(), -1);

	int64_t n = vect.size();

	for (int64_t i = 0; i < n; ++i)
	{
		while (!deq.empty() && vect[deq.back()] < vect[i]) 
		{
			nle[deq.back()] = vect[i];
			deq.pop_back();
		}

		deq.push_back(i);
	}

	return nle;
}

int main()
{
	int64_t test_cases = 0;
	std::cin >> test_cases;

	std::vector<int64_t> vect;

	for (int64_t i = 0; i < test_cases; ++i)
	{
		int64_t n = 0;
		std::cin >> n;
		vect.reserve(n);

		for (int64_t j = 0; j < n; ++j)
		{
			int64_t x = 0;
			std::cin >> x;
			vect.push_back(x);
		}

		std::vector<int64_t> nle = next_larger_element(vect);

		for (auto it = nle.begin(); it != nle.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << "\n";

		vect.clear();
	}
}