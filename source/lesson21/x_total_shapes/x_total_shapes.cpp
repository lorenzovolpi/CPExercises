#include <iostream>
#include <vector>

void xts_visit(const std::vector<std::string>& matrix, std::vector<std::vector<int>>& colors, int i, int j, int n, int m) {
    colors[i][j] = 1;
    
    if(i >= 1 && matrix[i-1][j] == 'X' && colors[i-1][j] == 0) xts_visit(matrix, colors, i-1, j, n, m);
    if(j >= 1 && matrix[i][j-1] == 'X' && colors[i][j-1] == 0) xts_visit(matrix, colors, i, j-1, n, m);
    if(i < n - 1 && matrix[i+1][j] == 'X' && colors[i+1][j] == 0) xts_visit(matrix, colors, i+1, j, n, m);
    if(j < m - 1 && matrix[i][j+1] == 'X' && colors[i][j+1] == 0) xts_visit(matrix, colors, i, j+1, n, m);

    colors[i][j] = 2;
}

int xts(const std::vector<std::string>& matrix, int n, int m) {
    std::vector<std::vector<int>> colors;
    for(int i = 0; i<n; ++i) colors.emplace_back(m, 0);

    int sum = 0;
    for(int i = 0; i<n; ++i) {
        for(int j = 0; j<m; ++j) {
            if(matrix[i][j] == 'X' && colors[i][j] == 0) {
                ++sum;
                xts_visit(matrix, colors, i, j, n, m);
            }
        }
    }

    return sum;
}

int main() {
    int test_cases = 0;
    std::cin >> test_cases;
    std::vector<int> outp;

    for(int i = 0; i< test_cases; ++i) {
        int n, m;
        std::cin >> n;
        std::cin >> m;

        std::vector<std::string> matrix;
        for(int i = 0; i < n; ++i) {
            std::string st;
            std::cin >> st;
            matrix.push_back(st);
        }

        int res = xts(matrix, n, m);
        outp.push_back(res);
    }

    for(int i = 0; i < outp.size(); ++i) {
        std::cout << outp[i] << std::endl;
    }
}
