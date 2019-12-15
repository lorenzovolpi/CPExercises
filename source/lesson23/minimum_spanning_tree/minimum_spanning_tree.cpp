#include <iostream>
#include <vector>
#include <algorithm>

struct disjoint_set
{
    int x, n = 1;
    disjoint_set *next = NULL, *prev = this, *r;

    disjoint_set(int x) : x(x) {
        r = this;
    }

    void merge(disjoint_set* m) {
        disjoint_set *last = this->r->prev, *firstm = m->r;

        last->next = firstm;
        firstm->prev = last;
        this->r->n += firstm->n;

        while(firstm != NULL) {
            firstm->r = this->r;
            if(firstm->next == NULL) this->r->prev = firstm;
            firstm = firstm->next;
        }
    } 

    static void union_set(disjoint_set* s1, disjoint_set* s2) {
        if(s1->r->n > s2->r->n) s1->merge(s2);
        else s2->merge(s1);
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
    std::vector<disjoint_set*> sets;
    for(int i = 0; i<n; ++i) sets.push_back(new disjoint_set(i));
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
        disjoint_set *s1 = sets[edges[i].u], *s2 = sets[edges[i].v];
        if(s1->r != s2->r) {
            disjoint_set::union_set(s1, s2);
            sum += edges[i].w;
        }
    }

    std::cout << sum << std::endl;

}