#include <iostream>
#include <vector>
#include <algorithm>

int lis(const std::vector<int>& items, int start, int end) {
    if (start == end) return 1;
    std::vector<int> subs(items.size(), 1);
    int max = 1;
    bool inc = end - start > 0;
    for(int i = start + (inc ? 1 : -1); (inc && i <= end || !inc && i >= end); i += (inc ? 1 : -1)) {
        int imax = 0;

        for(int j = (inc ? i-1 : i+1); (inc && j>=start || !inc && j<=start); j -= (inc ? 1 : -1)) {
            if(items[j] < items[i]) {
                if(subs[j] > imax) imax = subs[j];
            }
        }

        subs[i] = imax + 1;
        if(subs[i] > max) max = subs[i];
    }

    return max;
}

int lbs(const std::vector<int>& items) {

    int max = 0;
    for(int i = 0; i<items.size(); ++i) {
        int imax = lis(items, 0, i) + lis(items, items.size() - 1, i) - 1;
        if (imax > max) max = imax;
    }

    return max;
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

        int max = lbs(values);

        outp.push_back(max);
        values.clear();
    }

    for(int i = 0; i<test_cases; ++i) {
        std::cout << outp[i] << std::endl;
    }
}