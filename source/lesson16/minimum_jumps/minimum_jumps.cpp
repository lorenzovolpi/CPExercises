#include <iostream>
#include <vector>
#include <algorithm>

/*
    The problem is solved using dynamic programming. We use an array of length n, the same as
    the length of the input. At each position i we go back through the orriginal array and find
    each element with a distance to the current position less than or equal to the value of the
    computed element in the original array. Then the value in the computed array is checked and
    the minumum found is set at current position, increased by 1. The Algorithm runs in O(n^2) 
    in time.
*/

int minimum_jumps(const std::vector<int>& items) {
    std::vector<int> jumps(items.size(), 0);

    for(int i = 1; i < jumps.size(); ++i) {
        int min = items.size() - 1;

        for(int j = i-1; j>=0; --j) {
            if(items[j] >= i - j) {
                if(jumps[j] < min) min = jumps[j];
            }
        }

        jumps[i] = min + 1;
    }

    return (jumps[jumps.size() - 1] < items.size() ? jumps[jumps.size() - 1] : -1);
}

int main() {
    int test_cases = 0;
    std::cin >> test_cases;
    std::vector<int> values;
    std::vector<int> outp;
    outp.reserve(test_cases);
    
    for(int i = 0; i<test_cases; ++i) {
        int n = 0;
        std::cin >> n;
        values.reserve(n);
        for(int j = 0; j<n; ++j) {
            int v = 0;
            std::cin >> v;
            values.push_back(v);
        }

        int subs = minimum_jumps(values);

        outp.push_back(subs);
        values.clear();
    }

    for(int i = 0; i<test_cases; ++i) {
        std::cout << outp[i] << std::endl;
    }
}