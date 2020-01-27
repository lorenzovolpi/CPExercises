#include <iostream>
#include <vector>
#include <algorithm>

/*
    The problem is solved using dynamic programming. We use a table n*m where
    n and m are the lengths of the two strings and each row corresponds to a char
    of the first string and each column to a char of the second string. At any position
    [i][j] we have the lcs of the prefix of length i of the first string and the prefix
    of length j of the second string. The solution is found in O(n*m) time complexity.
*/

int lcs_len(std::string st1, int len1, std::string st2, int len2) {
    
    std::vector<std::vector<int>> matrix;
    matrix.reserve(len1 + 1);
    for(int i = 0; i <= len1; ++i) matrix.emplace_back(len2 + 1, 0);

    for(int i = 1; i<=len1; ++i) {
        for(int j = 1; j<=len2; ++j) {
            if(st1[i-1] == st2[j-1]) matrix[i][j] = matrix[i-1][j-1] + 1;
            else matrix[i][j] = std::max(matrix[i-1][j], matrix[i][j-1]);
        }
    }

    return matrix[len1][len2];
}

int main() {
    int test_cases = 0;
    std::cin >> test_cases;
    std::vector<int> outp;
    outp.reserve(test_cases);

    for(int i = 0; i<test_cases; ++i) {
        int len1 = 0, len2 = 0;
        std::cin >> len1;
        std::cin >> len2;

        std::string st1, st2;
        std::cin >> st1;
        std::cin >> st2;

        int lcs = lcs_len(st1, len1, st2, len2);

        outp.push_back(lcs);
    }

    for(int i = 0; i<outp.size(); ++i) {
        std::cout << outp[i] << std::endl;
    }

}