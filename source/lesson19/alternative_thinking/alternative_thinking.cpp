#include <iostream>
#include <algorithm>

/*
    For this solution we compute the greedy sequence of alternating 0 and 1
    in a greedy fashion in O(n) time. Then, as inverting a contiguos subsequnce
    we can increase the computed length at most by 2, we compute the minimum
    between the length of the wntire sequence and the increased value computed.
    The result can be found in O(n) in time.
*/

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
