#include <iostream>
#include <vector>
#include <algorithm>

/*
    This problm is solved using dynamic programming. The input array is scanned
    fron left to right and a support list is kept, initially empty. For each element
    of the input array, if it is grater than the last element of the support list, the
    element is added to the end, otherwise we can we can use binary search to find
    the smallest element in the list greater than the current element and replace the former
    with the latter. The LIS is the length of the support list. This solutions runs in
    O(nlogn) in time.
*/

int bs(const std::vector<int> &v, int s, int e, int x) {
    int mid = (s + e) / 2;
    if(s == e) return s;
    if(v[mid] >= x) return bs(v, s, mid, x);
    else return bs(v, mid + 1, e, x);
}

int lis(const std::vector<int>& items) {
    std::vector<int> dl(1);
    dl[0] = items[0];
    for(int i = 1; i<items.size(); ++i) {
        if(items[i] > dl.back()) {
            dl.push_back(items[i]);
        } else {
            int r = bs(dl, 0, dl.size() - 1, items[i]);
            dl[r] = items[i];
        }
    }

    return dl.size();
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