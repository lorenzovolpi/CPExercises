#include <iostream>
#include <vector>

/*
	This solution parses the array from right to left momorizing the current max.
	If the current element is grater than or equal to the current max it is added to 
	the leadersand current max is updated. Laste element is always a leader. The algorithm
	runs in O(n).
*/

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

		for (int j = 0; j < n; ++j) 
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