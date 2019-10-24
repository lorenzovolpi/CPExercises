#include <iostream>
#include <vector>
#include <deque>

std::vector<int> next_larger_element(std::vector<int> vect)
{
	std::deque<int> deq;
	std::vector<int> nle;
	nle.reserve(vect.size());

	int n = vect.size();

	for (int i = 0; i < n; ++i)
	{
		while (!deq.empty() && vect[deq.back()] < vect[i]) 
		{
			deq.pop_back();
			nle.push_back(vect[i]);
		}

		deq.push_back(i);
	}

	while (!deq.empty()) 
	{
		deq.pop_back();
		nle.push_back(-1);
	}

	return nle;
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

		std::vector<int> nle = next_larger_element(vect);

		for (auto it = nle.begin(); it != nle.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << "\n";

		vect.clear();
	}
}