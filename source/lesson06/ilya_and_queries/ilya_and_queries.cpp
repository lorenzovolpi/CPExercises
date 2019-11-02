#include <iostream>
#include <vector>

int main()
{
	std::string s;
	std::cin >> s;
	int len = s.length();

	std::vector<int> vec;
	vec.reserve(len);

	for (int i = 0; i < len; ++i) vec.push_back(0); 

	for (int i = 0; i < len - 1; i++)
	{
		if (s[i] == s[i + 1]) vec[i] = i == 0 ? 1 : vec[i - 1] + 1;
		else vec[i] = i == 0 ? 0 : vec[i - 1];
	}

	int n = 0;
	std::cin >> n;

	for (int i = 0; i < n; ++i)
	{
		int j, k;

		std::cin >> j;
		std::cin >> k;

		--j, --k;

		int res = (k == 0 ? 0 : vec[k - 1]) - (j == 0 ? 0 : vec[j - 1]);

		std::cout << res << std::endl;
	}

}