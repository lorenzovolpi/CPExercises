#include <iostream>
#include <vector>
#include <algorithm>

/*
    This problem is solved using dynamic programming. A table of size n*n is built
    and element at position [i][j] indicates if longest palindromic subsequence from 
    i to j. To compute each element of the table we check if elements at position i and j
    are equal; if so the solution is [i+1][j-1] + 2, else is the maximum value between
    [i+1][j] and [i][j-1]. The solution runs in O(n^2);
*/

int lps(const std::string& st) {
    std::vector<std::vector<int>> matrix;
    for(int i = 0; i<st.length(); ++i) matrix.emplace_back(st.length(), 0);

    for(int i = 0; i<st.length(); ++i) matrix[i][i] = 1;
    for(int j = 1; j<st.length(); ++j) {
        for(int i = 0; i+j < st.length(); ++i) {
            if(st[i] == st[i+j]) matrix[i][i+j] = 2 + matrix[i+1][i+j-1];
            else matrix[i][i+j] = std::max(matrix[i+1][i+j], matrix[i][i+j-1]);
        }
    }

    return matrix[0][st.length()-1];
}

int main() {
    int test_cases = 0;
    std::cin >> test_cases;
    std::vector<int> outp;
    outp.reserve(test_cases);

    for(int i = 0; i<test_cases; ++i) {
        std::string st;
        std::cin >> st;

        int max = lps(st);
        outp.push_back(max);
    }

    for(int i = 0; i<outp.size(); ++i) {
        std::cout << outp[i] << std::endl;
    }
}