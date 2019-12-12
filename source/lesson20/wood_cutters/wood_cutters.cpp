#include <iostream>
#include <vector>

struct tree{
    int x, h;

    tree(int x, int h) : x(x), h(h) {}
};

int wood_cut(std::vector<tree>& ts) {
    int cut = 1;
    for(int i = 1; i < ts.size(); ++i) {
        if(ts[i].x - ts[i].h > ts[i-1].x) cut++;
        else if((i < (ts.size() - 1) && ts[i].x + ts[i].h < ts[i+1].x) || i == ts.size() - 1) {
            cut++;
            ts[i].x += ts[i].h;
        }
    }

    return cut;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<tree> ts;
    for(int i = 0; i < n; ++i) {
        int x, h;
        std::cin >> x;
        std::cin >> h;
        ts.emplace_back(x, h);
    }

    int cut = wood_cut(ts);

    std::cout << cut << std::endl;

}
