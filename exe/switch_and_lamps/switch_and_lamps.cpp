#include <iostream>
#include <vector>

// https://codeforces.com/problemset/problem/985/B

int main() {
    int n, m;

    std::cin >> n >> m;
    std::vector<std::vector<int>> c(n, std::vector<int>(m, 0));
    std::vector<int> sum(m, 0);

    for(int i = 0; i<n; ++i) {
        std::string s;
        std::cin >> s;
        for(int j = 0; j<m; ++j) {
            c[i][j] = (s[j] == '0' ? 0 : 1);
            sum[j] += c[i][j];
        }
    }

    bool aa;
    for(int i = 0; i<n; ++i) {
        aa = true;
        for(int j = 0; j<m && aa; ++j) {
            if(sum[j] - c[i][j] == 0) {
                aa = false;
            }
        }
        if(aa) break;
    }

    std::cout << (aa ? "YES" : "NO") << std::endl;
}
