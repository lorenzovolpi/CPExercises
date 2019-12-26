#include <iostream>
#include <vector>
#include <functional>

int inverse_compare(const int& i1, const int& i2)
{
	return -(i1 - i2);
}

int invcnt_merge(std::vector<int>& A, int f, int half, int l, std::function<int(int, int)> compare)
{
	std::vector<int> v1, v2;
	v1.reserve(half + 1);
	v2.reserve(l - f - half);
	int invcnt = 0;

	for (int i = f; i <= f + half; ++i) v1.push_back(A[i]);
	for (int i = f + half + 1; i <= l; ++i) v2.push_back(A[i]);

	int i = f, j = 0, k = 0;
	for (; i <= l && j < (half + 1) && k < (l - f - half);)
	{
		if (compare(v1[j], v2[k]) < 0) {
			A[i] = v1[j];
			++j; ++i;
			invcnt += (l - f - half - k);
		}
		else if (compare(v1[j], v2[k]) > 0)
		{
			A[i] = v2[k];
			++k; ++i;
		}
		else
		{
			A[i] = v1[j];
			A[i + 1] = v2[k];
			++j; ++k;
			i += 2;
		}
	}

	for (; i <= l && j < (half + 1); ++j, ++i)
	{
		A[i] = v1[j];
	}

	for (; i <= l && k < (l - f - half); ++k, ++i)
	{
		A[i] = v2[k];
	}

	return invcnt;
}

int invcnt_merge_sort(std::vector<int>& A, int f, int l)
{
	if (l - f == 0) return 0;

	int half = (l - f) / 2;
	int invcnt = 0;

	invcnt += invcnt_merge_sort(A, f, f + half);
	invcnt += invcnt_merge_sort(A, f + half + 1, l);

	invcnt += invcnt_merge(A, f, half, l, inverse_compare);

	return invcnt;
}

int main()
{
	int test_cases = 0;
	std::cin >> test_cases;

	std::vector<int> vec;

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
		
		int invcnt = invcnt_merge_sort(vec, 0, n-1);

		std::cout << std::endl << invcnt <<  std::endl;

		vec.clear();
	}
}