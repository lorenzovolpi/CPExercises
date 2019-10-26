#include "sort.h"

int default_compare(const int &i1, const int &i2)
{
	return i1 < i2;
}

void merge_sort(std::vector<int>& A, int f, int l, std::function<int(int, int)> compare)
{

}

void merge_sort(std::vector<int>& A, int f, int l)
{
	merge_sort(A, f, l, default_compare);
}