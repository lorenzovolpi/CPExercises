#include <iostream>
#include <vector>

/*
    The problem is solved using a variant of classic DFS visit. Each node, during
    visit, is colored alternating two different sets of colors. If each node can
    be colored following the pattern the bipartite graph property holds. The 
    computational cost of the algorithm is equal to the one of DFS visit, so
    the algorithm runs in linear time over the graph.
*/

bool visit(const std::vector<std::vector<int>>& matrix, std::vector<int>& colors, int i, int n, int c) {
    colors[i] = c;
    bool res = true;
    for(int j = 0; j<n && res; ++j) {
        if(matrix[i][j] == 1) {
            int cc = (c + 1) % 2;
            if(colors[j] == -1) {
                res = res && visit(matrix, colors, j, n, cc);
            } else if(colors[j] != cc && colors[j] != cc+2) res = false;
        }
    }
    colors[i] = c + 2;
    return res;
}

bool is_bipartite(const std::vector<std::vector<int>>& matrix, int n) {
    std::vector<int> colors(n, -1);
    bool res = true;
    for(int i = 0; i<n; ++i) {
        if(colors[i] == -1) {
            res = res && visit(matrix, colors, i, n, 0);
        }
    }

    return res;
}

int main() {
    int test_cases = 0;
    std::cin >> test_cases;
    std::vector<int> outp;
    for(int i = 0; i<test_cases; ++i) {
        int n;
        std::cin >> n;
        std::vector<std::vector<int>> matrix;
        for(int i = 0; i<n; ++i) {
            matrix.emplace_back(n);
            for(int j = 0; j<n; ++j) {
                int x;
                std::cin >> x;
                matrix[i][j] = x;
            }
        }

        outp.push_back(is_bipartite(matrix, n) ? 1 : 0);
    }

    for(int i = 0; i<outp.size(); ++i) {
        std::cout << outp[i] << std::endl;
    }
}
