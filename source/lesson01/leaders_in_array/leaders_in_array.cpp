#include <iostream>
#include <vector>

int main() {

	std::vector<int> vec;

	int n = 0;
	std::cin >> n;
	vec.reserve(n);

	for (int i = 0; i < n; ++i) {
		int x = 0;
		std::cin >> x;
		vec.push_back(x);
	}

	for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
		std::cout << *it << " ";
	}

	return 0;
}