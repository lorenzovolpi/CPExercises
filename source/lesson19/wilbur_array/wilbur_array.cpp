#include <iostream>
#include <vector>
#include <cstdlib>

typedef long long llong;

llong wilbur_steps(const std::vector<llong>& arrb) {

    llong cv = 0, steps = 0;
    for(int i = 0; i<arrb.size(); ++i) {
        steps += std::abs(arrb[i] - cv);
        cv = arrb[i];
    }

    return steps;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<llong> arrb;
    arrb.reserve(n);
    for(int i = 0; i<n; ++i) {
        llong x = 0;
        std::cin >> x;
        arrb.push_back(x);

    }

    llong min = wilbur_steps(arrb);
    std::cout << min << std::endl;
}
