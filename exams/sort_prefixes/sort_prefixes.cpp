#include <iostream>
#include <vector>
#include <algorithm>

struct query{
    int op, i;

    query(int op, int i) : op(op), i(i) {}
};

int main() {
    int n, m;

    std::cin >> n >> m;

    std::vector<int> v(n);

    for(int i = 0; i<n; ++i) std::cin >> v[i];

    std::vector<query> input;
    for(int i = 0; i<m; ++i) {
        int op, ind;
        std::cin >> op >> ind;
        input.emplace_back(op, ind-1);
    }

    int last = -1;
    std::vector<query> prsd;
    for(int i = m-1; i>=0; --i) {
        if(input[i].i > last) {
            last = input[i].i;
            prsd.emplace_back(input[i].op, input[i].i);
        }
    }


    std::vector<int> sv(n);
    std::copy(v.begin(), v.end(), sv.begin());
    std::sort(sv.begin(), sv.begin() + prsd.back().i + 1);
    int smlst = -1, grtst = prsd.back().i + 1;

    for(int j = prsd.size() - 1; j >= 0; --j) {
        int diff = j > 0 ? prsd[j].i - prsd[j-1].i : prsd[j].i + 1;
        for(int k = 0; k<diff; ++k) {
            if(prsd[j].op == 1) {
                v[prsd[j].i-k] = sv[--grtst];
            } else if (prsd[j].op == 2) {
                v[prsd[j].i - k] = sv[++smlst];
            }
        }
    }

    for(int i = 0; i<n; ++i) std::cout << v[i] << " ";
    //std::cout << std::endl;

}
