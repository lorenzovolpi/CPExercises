#include <iostream>
#include <vector>
#include <algorithm>

/*
	The idea is to firstly sort all the elements by decreasing value. Then
	Each element is computed and to each element is associated h1 or h2, in 
	alternating fashion. If a value is present more than twice, only the first 
	two elements with same value are considered in this prosess, leaving all 
	other elements outside of the two heaps. A variable c is kept counting
	all elements which contribute to generate distinct final numbers from
	the two heaps. Now the number of different possible numbers is printed
	and the remaining elements are assigned to the two heaps, until h1 and
	h2 are equal to n. All the elements are now sorted back to original order
	and the values of the corresponding heaps are printed. The algorithm runs in
	O(nlogn).
*/

struct cube
{
	int i, v, h;

	cube(int index, int value) : i(index), v(value), h(0){}
};

int main()
{
	int n = 0;
	std::cin >> n;
	std::vector<cube> arr;
	arr.reserve(2 * n);

	for (int i = 0; i < 2 * n; i++)
	{
		int x;
		std::cin >> x;
		arr.emplace_back(i, x);
	}

	std::sort(arr.begin(), arr.end(), [](cube c1, cube c2)
		{
			return c1.v > c2.v;
		});

	int c = 1, eqc = 0, h1 = 0, h2 = 0;
	for (int i = 0, h = -1; i < 2 * n; i++)
	{
		if(i > 0) {
			if(arr[i].v == arr[i - 1].v) {
				if(eqc == 0) {
					c++;
					eqc++;
					arr[i].h = (++h % 2) + 1;
					if((h % 2) + 1 == 1) h1++;
					else h2++;
				}
			}
			else {
				eqc = 0;
				c++;
				arr[i].h = (++h % 2) + 1;
				if((h % 2) + 1 == 1) h1++;
				else h2++;
			}
		} else {
			arr[i].h = (++h % 2) + 1;
			if((h % 2) + 1 == 1) h1++;
			else h2++;
		}
		
	}

	for(int i = 0; i<2*n; ++i) {
		if(arr[i].h == 0) {
			if(h2 < n) {
				arr[i].h = 2;
				h2++;
			} else if(h1 < n) {
				arr[i].h = 1;
				h1++;
			} else {
				break;
			}
		}
	}

	std::cout << (c/2)*(c - c/2) << std::endl;

	std::sort(arr.begin(), arr.end(), [](cube c1, cube c2)
		{
			return c1.i < c2.i;
		});

	for (int i = 0; i < 2 * n; i++) std::cout << arr[i].h << " "; 
	std::cout << std::endl;
}