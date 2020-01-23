#include <iostream>
#include <vector>

/*
	This solution computes a suffix sum of the number of suffixes which
	sum is equal to total sum the array divided by 3. The the array is scanned
	from left to right and when the current prefix sum of the array is 1/3 of the total sum
	the value of the previously computed suffix sum at position i+2 is added to the result.
	Alforithm runs in O(n).
*/

int main()
{
	int64_t n = 0, sum = 0;
	std::cin >> n;
	std::vector<int64_t> vec, suff;
	vec.reserve(n);
	suff.reserve(n);

	for (int64_t i = 0; i < n; ++i)
	{
		int64_t x = 0;
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

	int64_t ssum = 0;
	for (int64_t i = n - 1; i >= 0; --i)
	{
		ssum += vec[i];
		if (ssum == sum / 3) suff[i] = (i + 1 == n ? 1 : suff[i + 1] + 1);
		else suff[i] = (i + 1 == n ? 0 : suff[i + 1]);
	}

	int64_t psum = 0, res = 0;
	for (int64_t i = 0; i < n; i++)
	{
		psum += vec[i];
		if (psum == sum / 3)
		{
			res += (i + 2 >= n ? 0 : suff[i + 2]);
		}
	}

	std::cout << res << std::endl;
}