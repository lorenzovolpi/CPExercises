// largest_even_number.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

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

void merge_sort(std::vector<int>& A, int f, int l, std::function<int(int, int)> compare)
{
	if (l - f == 0) return;

	int half = (l - f) / 2;

	merge_sort(A, f, f + half, compare);
	merge_sort(A, f + half + 1, l, compare);

	merge(A, f, half, l, compare);

	return;
}

void largest_even(std::vector<int>& digits)
{
	int min_e_i = 0, min_e = 10;

	for (int i = 0; i < digits.size(); ++i)
	{
		if (digits[i] % 2 == 0) 
		{
			if (digits[i] < min_e)
			{
				min_e = digits[i];
				min_e_i = i;
			}
		}
	}

	if (min_e < 10)
	{
		digits.erase(digits.begin() + min_e_i);
	}

	merge_sort(digits, 0, digits.size() - 1, [](const int &i1, const int &i2)
		{
			return -(i1 - i2);
		});

	if (min_e < 10) {
		digits.push_back(min_e);
	}

}

std::vector<int> split_num(const std::string &num)
{
	std::vector<int> digits;
	digits.reserve(num.length());

	for (auto it = num.cbegin(); it != num.cend(); ++it)
	{
		digits.push_back((int)(*it - '0'));
	}

	return digits;
}

int main()
{
	int test_cases = 0;
	std::cin >> test_cases;

	for (int i = 0; i < test_cases; ++i)
	{
		std::string num;
		std::cin >> num;

		std::vector<int> digits = split_num(num);

		largest_even(digits);

		for (auto it = digits.begin(); it != digits.end(); ++it)
		{
			std::cout << *it;
		}
		std::cout << "\n";
	}
}
