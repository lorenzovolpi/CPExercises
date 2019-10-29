//sort.h
#include <vector>
#include <functional>

void merge_sort(std::vector<int>& A, int f, int l);

void merge_sort(std::vector<int>& A, int f, int l, std::function<int(int, int)> compare);

int invcnt_merge_sort(std::vector<int>& A, int f, int l);