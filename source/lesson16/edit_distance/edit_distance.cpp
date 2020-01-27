#include <iostream>
#include <vector>
#include <algorithm>

/*
    The problem is solved using dynamic programming. We use a table n*m where
    n and m are the lengths of the two strings and each row corresponds to a char
    of the first string and each column to a char of the second string. At any position
    [i][j] we have the edit distance between the prefix of length i of the first string 
    and the prefix of length j of the second string. The solution is found in O(n*m) 
    time complexity.
*/

template <typename T>
T min3 (T a, T b, T c) {
    return a <= b ? (a <= c ? a : c) :
                    (b <= c ? b : c);
}

int edit_distance(const std::string& st1, const std::string& st2) {

    std::vector<std::vector<int>> matrix;
    matrix.reserve(st2.length() + 1);
    for(int i = 0; i <= st2.length(); ++i) {
        matrix.emplace_back(st1.length() + 1, 0);
        matrix[i][0] = i;
    }
    for(int i = 1; i<=st1.length(); ++i) matrix[0][i] = i;

    for(int i = 1; i<=st2.length(); ++i) {
        for(int j = 1; j<=st1.length(); ++j) {
            if(st2[i-1] == st1[j-1]) matrix[i][j] = matrix[i-1][j-1];
            else matrix[i][j] = min3(matrix[i-1][j-1], matrix[i-1][j], matrix[i][j-1]) + 1;
        }
    }

    return matrix[st2.size()][st1.size()];
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

        int ed = edit_distance(st1, st2);

        outp.push_back(ed);
    }

    for(int i = 0; i<test_cases; ++i) {
        std::cout << outp[i] << std::endl;
    }
}