// largest_even_number.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "../../../lib/sort.h"

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
