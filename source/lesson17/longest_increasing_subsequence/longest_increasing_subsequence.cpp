#include <iostream>
#include <vector>
#include <algorithm>

int lis(const std::vector<int>& items) {
    std::vector<int> subs(items.size(), 1);
    int max = 1;
    for(int i = 1; i < subs.size(); ++i) {
        int imax = 0;

        for(int j = i-1; j>=0; --j) {
            if(items[j] < items[i]) {
                if(subs[j] > imax) imax = subs[j];
            }
        }

        subs[i] = imax + 1;
        if(subs[i] > max) max = subs[i];
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

        int max = lis(values);

        outp.push_back(max);
        values.clear();
    }

    for(int i = 0; i<test_cases; ++i) {
        std::cout << outp[i] << std::endl;
    }
}