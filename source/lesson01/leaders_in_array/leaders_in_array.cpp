#include <iostream>
#include <vector>


void print_leaders_in_array(std::vector<int> vect) {

	std::vector<int> leaders;
	leaders.reserve(vect.size());

	int max = *vect.rbegin();

	for (auto it = vect.rbegin(); it != vect.rend(); ++it) {
		if (*it >= max) {
			max = *it;
			leaders.push_back(max);
		}
	}

	for (auto it = leaders.rbegin(); it != leaders.rend(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << "\n";
}


int main() {

	std::vector<int> vec;
	int test_cases = 0;

	std::cin >> test_cases;
	
	for (int i = 0; i < test_cases; ++i) 
	{
		int n = 0;
		std::cin >> n;
		vec.reserve(n);

		for (int i = 0; i < n; ++i) 
		{
			int x = 0;
			std::cin >> x;
			vec.push_back(x);
		}

		print_leaders_in_array(vec);

		vec.clear();
	}

	return 0;
}