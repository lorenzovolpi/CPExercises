#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

/*
    To solve the problem we first need to sort all the people originary in the queue in
    increasing order of the a value. Now the array is scanned and if and a value is grater
    than its index no possible ordering is possible. Now we need to build a possible ordering
    of the queue and this can be done in linear time using an auxiliary stack. We keep two 
    indeces: the first scans the people array from right to left and the second keeps the current
    available position in the array. When i and the a value of i element of people array are equal
    we put that person in position j, otherwise if j is greater we push j on the stack and decrease j
    and if j is less we puth the ith element in the top position of the stack and decrease i. In this
    way at each iteration we keep a stack of indeces, from the nearest to the furthest, of avaliable
    positions for the ith element, from ps[i]->a on. People sorted this way are then assigned a height 
    value decreasing from left to right. The algorithm runs in O(nlogn) in time.
*/

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

    for(int i = ps.size() - 1, j = ps.size() - 1; i>=0; ) {
        if(j == ps[i]->a) {
            bk.push_front(j);
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
