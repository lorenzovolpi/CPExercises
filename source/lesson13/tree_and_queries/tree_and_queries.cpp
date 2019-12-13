#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct edge{
    int u, v;

    edge(int u, int v) : u(u), v(v) {}
};

struct query{
    int v, k;
    int a = -1, i;

    query(int v, int k, int i) : v(v), k(k), i(i) {}
};

struct tree{
    int value;
    int f = -1, l = -1, c = 0;
    std::vector<tree*> children;

    tree(int v) : value(v) {}

    bool add(int p, int v) {
        bool res = false;
        if(this->value == p) {
            this->children.push_back(new tree(v));
            res = true;
        } else {
            for(int i = 0; i<this->children.size() && !res; ++i) {
                res = res || this->children[i]->add(p, v);
            }
        }

        return res;
    }
};

void linearize_tree(const std::vector<int>& colors, tree* root, std::vector<tree*>& lin, int& time) {
    int ri = ++time;
    lin[ri] = root;
    root->f = ri;
    root->c = colors[(root->value) - 1] - 1;

    for(int i = 0; i<root->children.size(); ++i) {
        linearize_tree(colors, root->children[i], lin, time);
    }

    root->l = time;
}

tree* build_tree(std::vector<edge> edges) {
    tree* root = new tree(edges[0].u);
    for(int i = 0; i<edges.size(); ++i) root->add(edges[i].u, edges[i].v);

    return root;
}

int main() {
    int n, m;
    std::cin >> n;
    std::cin >> m;
    std::vector<int> colors;
    std::vector<edge> edges;
    std::vector<query> queries;
    for(int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        colors.push_back(x);
    }
    for(int i = 0; i<n-1; ++i) {
        int u, v;
        std::cin >> u;
        std::cin >> v;
        edges.emplace_back(u, v);
    }

    tree* root = build_tree(edges);
    std::vector<tree*> lind(n);
    int time = -1;
    linearize_tree(colors, root, lind, time);

    std::vector<tree*> srtd(n, NULL);
    for(int i = 0; i<n; ++i) {
        srtd[(lind[i]->value) - 1] = lind[i];
    }

    for(int i = 0; i<m; ++i) {
        int v, k;
        std::cin >> v;
        std::cin >> k;

        queries.emplace_back(srtd[v - 1]->f, k, i);
    }

    std::sort(queries.begin(), queries.end(), [](query q1, query q2){
        if(q1.v == q2.v) {
            return q1.k > q2.k;
        } else return q1.v < q2.v;
    });

    int lb = -1;
    std::vector<int> colormap(n, 0), ks(n, 0);
    for(int i = 0; i<lind.size(); ++i) colormap[lind[i]->c]++;

    for(int i = 0; i<colormap.size(); ++i) ks[colormap[i]]++;
    int sum = 0, lastk = -1;
    int old_f = 0, old_l = lind.size() - 1;
    for(int j = ks.size() - 1; j>=queries[0].k; --j) sum+=ks[j];
    lastk = queries[0].k;
    queries[0].a = sum;
    for(int i = 1; i<queries.size(); ++i) {
        int cf = queries[i].v, cl = lind[queries[i].v]->l;
        if(cf != old_f) {
            if(old_l < cl) {
                old_l++;
                while(old_l <= cl) {
                    int c = lind[old_l]->c;
                    int oldk = colormap[c];
                    colormap[c]++;
                    ks[colormap[c]]++;
                    ks[oldk]--;
                    old_l++;
                }
                old_l--;
            }
            while(old_f < cf) {
                int c = lind[old_f]->c;
                int oldk = colormap[c];
                colormap[c]--;
                ks[colormap[c]]++;
                ks[oldk]--;
                old_f++;
            }
            while(old_l > cl) {
                int c = lind[old_l]->c;
                int oldk = colormap[c];
                colormap[c]--;
                ks[colormap[c]]++;
                ks[oldk]--;
                old_l--;
            }
            sum = 0;
            for(int j = ks.size() - 1; j>=queries[i].k; --j) sum+=ks[j];
            lastk = queries[i].k;
            queries[i].a = sum;
        } else {
            int ck = queries[i].k;
            lastk--;
            while(lastk >= ck) {
                sum += ks[lastk];
                lastk--;
            }
            queries[i].a = sum;
        }
    }
    
    std::sort(queries.begin(), queries.end(), [](query q1, query q2){
        return q1.i < q2.i;
    });
    
    for(int i = 0; i<queries.size(); ++i) {
        std::cout << queries[i].a << std::endl;
    }
}
