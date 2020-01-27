#include <iostream>
#include <vector>
#include <deque>
#include <fstream>

struct elem{
    int v, s = -1, e = -1;

    elem(int v) : v(v){}
};

std::vector<int> next_smaller_element(const std::vector<int> &a) {
    std::deque<int> deq;
    std::vector<int> nse(a.size(), a.size() + 2);
    for(int i = 0; i<a.size(); ++i) {
        while(!deq.empty() && a[deq.back()] > a[i]) {
            nse[deq.back()] = i;
            deq.pop_back();
        }
        deq.push_back(i);
    }

    return nse;
}

int main(int argc, char** argv) {
    int n;
    std::cin >> n;
    
    std::vector<elem*> a(n);
    std::vector<int> v(n, 0);
    for(int i = 0; i<n; ++i) a[i] = new elem(i+1);
    bool res = true;
    for(int i = 0; i<n; ++i) {
        int x;
        std::cin >> x;
        if ( x < 1 || x > n ) {
            res = false;
            break;
        }
        if(a[x-1]->s == -1) {
            a[x-1]->s = i;
            a[x-1]->e = i;
        } else a[x-1]->e = i;

        v[i] = x;
    }

    if(!res) {
        std::cout << "N" << std::endl;
        return 0;
    }

    std::vector<int> nse = next_smaller_element(v);

    for(int i = 0; i<v.size(); ++i) {
        if(a[v[i] - 1]->s == i) {
            if(nse[i] < a[v[i] - 1]->e) {
                res = false;
                break;
            }
        }
    }

    std::cout << (res ? "Y" : "N") << std::endl;
}