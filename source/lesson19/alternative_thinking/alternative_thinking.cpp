#include <iostream>
#include <algorithm>

int alternative(const std::string& num) {
    char last = num[0];
    int sum = 1;
    for(int i = 1; i<num.length(); ++i) {
        if(num[i] != last) {
            sum++;
            last = num[i];
        }
    }

    return std::min((std::size_t)sum + 2, num.length());
}

int main() {
    int n = 0;
    std::cin >> n;
    std::string num;
    std::cin >> num;

    int alt = alternative(num);

    std::cout << alt << std::endl;
}
