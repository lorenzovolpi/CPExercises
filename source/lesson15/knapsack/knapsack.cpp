#include <iostream>
#include <vector>
#include <algorithm>

struct item {
    int v, w;

    item(int value, int weight) : v(value), w(weight) {}
};

int knapsack(int capacity, const std::vector<item>& items) {
    
    std::vector<std::vector<int>> matrix;
    matrix.reserve(items.size() + 1);
    for(int i = 0; i <= items.size(); ++i) matrix.emplace_back(capacity + 1, 0);

    for(int i = 1; i<=items.size(); ++i) {
        for(int j = 1; j<=capacity; ++j) {
            if(items[i-1].w > j) matrix[i][j] = matrix[i-1][j];
            else matrix[i][j] = std::max(matrix[i-1][j], matrix[i-1][j - items[i-1].w] + items[i-1].v);
        }
    }

    return matrix[items.size()][capacity];
}

int main() {
    int capacity = 0, nitem = 0;
    std::cin >> capacity;
    std::cin >> nitem;
    std::vector<item> items;
    items.reserve(nitem);

    for(int i = 0; i<nitem; ++i) {
        int weight = 0, value = 0;
        std::cin >> weight;
        std::cin >> value;

        items.emplace_back(value, weight);
    }

    int mval = knapsack(capacity, items);

    std::cout << mval << std::endl;
}