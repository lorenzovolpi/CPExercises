#include <iostream>
#include <vector>
#include <algorithm>

/*
    The solution to this problem is reached through dynamic programming. We keep a table of 
    n*s elements, where s if the sum of all original elements halved. At each position
    [i][j] we have a boolean value indicating if there exists a sumbset of the first i elements
    which sums up to j. The solution can be found, after the table is filled, at right-bottom
    corner of the table and the algorithm runs in O(n*s) in time.
*/

bool subset_sum(const std::vector<int>& items) {
    int sum = 0;
    for(int i = 0; i<items.size(); ++i) sum += items[i];

    if(sum % 2 != 0) return false;

    sum /= 2;

    std::vector<std::vector<bool>> matrix;
    matrix.reserve(items.size() + 1);
    for(int i = 0; i <= items.size(); ++i) {
        matrix.emplace_back(sum + 1, false);
        matrix[i][0] = true;
    }

    for(int i = 1; i<=items.size(); ++i) {
        for(int j = 1; j<=sum; ++j) {
            if(items[i-1] > j) matrix[i][j] = matrix[i-1][j];
            else matrix[i][j] = ( matrix[i-1][j] || matrix[i-1][j - items[i-1]] );
        }
    }

    return matrix[items.size()][sum];
}

int main() {
    int test_cases = 0;
    std::cin >> test_cases;
    std::vector<int> values;
    std::vector<bool> outp;
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

        bool subs = subset_sum(values);

        outp.push_back(subs);
        values.clear();
    }

    for(int i = 0; i<test_cases; ++i) {
        std::cout << (outp[i] ? "YES" : "NO") << std::endl;
    }
}