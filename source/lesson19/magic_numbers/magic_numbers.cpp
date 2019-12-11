#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> parse(int number) {
    std::vector<int> parsed;
    while(number != 0) {
        parsed.push_back(number % 10);
        number /= 10;
    }

    std::vector<int> result;
    for(int i = parsed.size() - 1; i>=0; --i) result.push_back(parsed[i]);
    return result;
}

bool is_magic(int number) {
    std::vector<int> parsed = parse(number);

    std::vector<int> comp(3);
    comp[0] = 1, comp[1] = 4, comp[2] = 4;

    bool magic = true;
    for(int i = 0, j = 0; i<parsed.size() && j < comp.size() && magic; ++i, ++j) {
        if(j == 0) {
            if(parsed[i] != comp[j]) magic = false;
        }
        else {
            if(parsed[i] != comp[j]) {
                if(parsed[i] == comp[0]) j = 0;
                else magic = false;
            } 
            if(j == 2) j = -1;
        }
    }

    return magic;
}

int main() {
    int number = 0;
    std::cin >> number;

    std::cout << (is_magic(number) ? "YES" : "NO") << std::endl;

}