#include <iostream>
#include <vector>
#include <algorithm>

/*
    The problem is solved using Kruskal's algorithm. Disjoint sets
    are implemented using trees with all common heuristics and runs
    in O(m*alpha(n)). The Kruskal's algorithm runs in O(|E|log|V|)
    in time.
*/

template <typename T>
struct disjset {
    T v;    
    disjset* p;
    int rank = 0;

    disjset(T v) : v(v) {
        this->p = this;
    }

    disjset* findSet() {
        if(this != this->p) {
            this->p = this->p->findSet();
        }
        return this->p;
    }

    static void unionSet(disjset* s1, disjset* s2){
        disjset *r1 = s1->findSet(), *r2 = s2->findSet();
        if(r1->rank > r2->rank) {
            r2->p = r1;
        } else if( r2->rank > r1->rank) {
            r1->p = r2;
        } else {
            r2->p = r1;
            r1->rank++;
        }
    }
};

struct edge{
    int u, v, w;

    edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

int main() {
    int n, m;
    std::cin >> n;
    std::cin >> m;
    std::vector<disjset<int>*> sets;
    for(int i = 0; i<n; ++i) sets.push_back(new disjset<int>(i));
    std::vector<edge> edges;
    for(int i = 0; i<m; ++i) {
        int u, v, w;
        std::cin >> u;
        std::cin >> v;
        std::cin >> w;
        edges.emplace_back(u-1, v-1, w);
    }

    std::sort(edges.begin(), edges.end(), [](edge e1, edge e2) {
        return e1.w < e2.w;
    });

    int sum = 0;
    for(int i = 0; i<m; ++i) {
        disjset<int> *s1 = sets[edges[i].u], *s2 = sets[edges[i].v];
        if(s1->findSet() != s2->findSet()) {
            disjset<int>::unionSet(s1, s2);
            sum += edges[i].w;
        }
    }

    std::cout << sum << std::endl;
}