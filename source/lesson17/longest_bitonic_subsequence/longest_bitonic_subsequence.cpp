#include <iostream>
#include <vector>
#include <algorithm>

/*
    The solution is computed using dynamic programming. The longest bitonic subsequence is
    computed using the LIS of the input array and of its reverse, each computed in O(nlogn)
    in time as seen during lessons. Then the resulting arrays are scanned the first from
    left to right and the second from right to left and the max of the sum of the two minus 1 is
    the requested LBS. The algorithm runs in O(nlogn) in time.
*/

int bs(const std::vector<int> &v, int s, int e, int x) {
    int mid = (s + e) / 2;
    if(s == e) return s;
    if(v[mid] >= x) return bs(v, s, mid, x);
    else return bs(v, mid + 1, e, x);
}

std::vector<int> lis(const std::vector<int>& items) {
    std::vector<int> dl(1);
    std::vector<int> subs(items.size(), 1);
    dl[0] = items[0];
    for(int i = 1; i<items.size(); ++i) {
        if(items[i] > dl.back()) {
            dl.push_back(items[i]);
            subs[i] = dl.size();
        } else {
            int r = bs(dl, 0, dl.size() - 1, items[i]);
            dl[r] = items[i];
            subs[i] = r+1;
        }
    }

    return subs;
}

std::vector<int> reverse(const std::vector<int>& v) {
    std::vector<int> res(v.size());
    for(int i = 0, j = v.size() - 1; i < v.size(); ++i, --j) {
        res[i] = v[j];
    }

    return res;
}

int lbs(const std::vector<int>& items) {

    std::vector<int> lisv = lis(items);
    std::vector<int> ldsv = lis(reverse(items));
    int max = 0;
    for(int i = 0, j = items.size() - 1; i<items.size(); ++i, --j) {
        if(lisv[i] + ldsv[j] - 1 > max) max = lisv[i] + ldsv[j] - 1;
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