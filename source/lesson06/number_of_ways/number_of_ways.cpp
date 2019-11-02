#include <iostream>
#include <vector>

int main()
{
	int n = 0, sum = 0;
	std::cin >> n;
	std::vector<int> vec, suff;
	vec.reserve(n);
	suff.reserve(n);

	for (int i = 0; i < n; ++i)
	{
		int x = 0;
		std::cin >> x;
		vec.push_back(x);
		suff.push_back(0);
		sum += x;
	}

	if (sum % 3 != 0)
	{
		std::cout << "0" << std::endl;
		return 0;
	}

	int ssum = 0;
	for (int i = n - 1; i >= 0; --i)
	{
		ssum += vec[i];
		if (ssum == sum / 3) suff[i] = i + 1 == n ? 1 : suff[i + 1] + 1;
		else suff[i] = i + 1 == n ? 0 : suff[i + 1];
	}

	int psum = 0, res = 0;
	for (int i = 0; i < n; i++)
	{
		psum += vec[i];
		if (psum == sum / 3)
		{
			res += i + 2 >= n ? 0 : suff[i + 2];
		}
	}

	std::cout << res << std::endl;

}