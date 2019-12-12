#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

struct person{
    std::string name;
    int a, h = 0;

    person(std::string name, int a) : name(name), a(a) {}

    void print() {
        std::cout << this->name << " " << this->h << std::endl;
    }
};

bool queue(std::vector<person*>& ps) {

    std::sort(ps.begin(), ps.end(), [](person* p1, person* p2) {
        return p1->a < p2->a;
    });

    for(int i = 0; i<ps.size(); ++i) if(ps[i]->a > i) return false;

    std::deque<int> bk;
    std::vector<person*> q(ps.size(), NULL);

    int last_a = ps.size();
    for(int i = ps.size() - 1, j = ps.size() - 1; i>=0; ) {
        if(j == ps[i]->a) {
            bk.push_front(j);
            last_a = ps[i]->a;
            q[bk.front()] = ps[i];
            bk.pop_front();
            --i; --j;
        } else if(j < ps[i]->a) {
            q[bk.front()] = ps[i];
            bk.pop_front();
            --i;
        } else {
            bk.push_front(j);
            --j;
        }
    }

    for(int i = 0, j=q.size(); i<q.size() && j > 0; ++i, --j) {
        if(q[i] != NULL) q[i]->h = j;
    }

    return true;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<person*> ps;

    for(int i = 0; i < n; ++i) {
        std::string name;
        int a;
        std::cin >> name;
        std::cin >> a;
        ps.push_back(new person(name, a));
    }

    if(queue(ps)) {
        for(int i=0; i<ps.size(); ++i) {
            ps[i]->print();
        }
    } else std::cout << -1 << std::endl;
}
