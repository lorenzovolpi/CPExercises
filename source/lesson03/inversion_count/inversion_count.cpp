#include <iostream>
#include <vector>

uint64_t invcnt_merge(std::vector<uint64_t>& A, uint64_t f, uint64_t half, uint64_t l)
{	
	std::vector<uint64_t> B((l-f) + 1);
	uint64_t invcnt = 0;
	uint64_t k = 0;
	uint64_t i = f, j = f + half + 1;

	while((i <= f + half) && (j <= l)) {
		if(A[i] < A[j]) {
			B[k++] = A[i++];
		} else if(A[i] > A[j]){
			B[k++] = A[j++];
			/* All following elements from position i in the first half of the array sum up to the inversion count */
			invcnt += f + half - i + 1;
		}
	}

	while(i <= f + half) {
		B[k++] = A[i++];
	}

	while(j <= l) {
		B[k++] = A[j++];
	}

	std::copy(B.begin(), B.end(), A.begin() + f);
	
	return invcnt;
}

uint64_t invcnt_merge_sort(std::vector<uint64_t>& A, uint64_t f, uint64_t l)
{
	if (l - f == 0) return 0;

	uint64_t half = (l - f) / 2;
	uint64_t invcnt = 0;

	invcnt += invcnt_merge_sort(A, f, f + half);
	invcnt += invcnt_merge_sort(A, f + half + 1, l);

	invcnt += invcnt_merge(A, f, half, l);

	return invcnt;
}

int main()
{
	uint64_t test_cases = 0;
	std::cin >> test_cases;

	std::vector<uint64_t> vec;

	for (uint64_t i = 0; i < test_cases; ++i)
	{
		uint64_t n = 0;
		std::cin >> n;
		vec.reserve(n);
		for (uint64_t j = 0; j < n; ++j)
		{
			uint64_t x = 0;
			std::cin >> x;
			vec.push_back(x);
		}
		
		uint64_t invcnt = invcnt_merge_sort(vec, 0, n-1);

		std::cout << invcnt <<  std::endl;

		vec.clear();
	}
}