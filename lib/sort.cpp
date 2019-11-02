#include "sort.h"

int default_compare(const int &i1, const int &i2)
{
	return i1 - i2;
}

int inverse_compare(const int& i1, const int& i2)
{
	return -(i1 - i2);
}

void merge(std::vector<int>& A, int f, int half, int l, std::function<int(int, int)> compare)
{
	std::vector<int> v1, v2;
	v1.reserve(half + 1);
	v2.reserve(l - f - half);

	for (int i = f; i <= f + half; ++i) v1.push_back(A[i]);
	for (int i = f + half + 1; i <= l; ++i) v2.push_back(A[i]);

	int i = f, j = 0, k = 0;
	for (; i <= l && j < (half + 1) && k < (l - f - half);)
	{
		if (compare(v1[j], v2[k]) < 0) {
			A[i] = v1[j];
			++j; ++i;
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

void merge_sort(std::vector<int>& A, int f, int l, std::function<int(int, int)> compare)
{
	if (l - f == 0) return;

	int half = (l - f) / 2;

	merge_sort(A, f, f + half, compare);
	merge_sort(A, f + half + 1, l, compare);

	merge(A, f, half, l, compare);

	return;
}

void merge_sort(std::vector<int>& A, int f, int l)
{
	merge_sort(A, f, l, default_compare);
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