#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

/*
    The algorithm is an application of Mo's algorithm on trees. The buckets
    are represented by subtrees and queries ar ordered by the position of the
    root of each subtree in the linearized tree and by k value in decreasing 
    order inside the same bucket. The array colormap stores the number of occurrences
    in a given subtree for each color and ks stores for each position i the number
    of colors occurring i times. 
*/

struct colorpos{
    int c, i;

    colorpos(int c, int i) : c(c), i(i) {}
};

struct query{
    int f, k, i;

    query(int v, int k, int i) : f(v), k(k), i(i) {}
};

struct tree{
    int value;
    int f = -1, l = -1, c = 0;
    std::vector<tree*> children;

    tree(int v, int c) : value(v), c(c) {}

    void addChild(tree* c) {
        this->children.push_back(c);
    }
};

void normalize_colors(std::vector<int>& colors) {
    std::vector<colorpos> cp(colors.size(), colorpos(0, 0));
    for(int i = 0; i<colors.size(); ++i) {
        cp[i].c = colors[i];
        cp[i].i = i;
    }
    std::sort(cp.begin(), cp.end(), [](colorpos cp1, colorpos cp2) {
        return cp1.c < cp2.c;
    });
    colors[cp[0].i] = 1;
    for(int i = 1; i<cp.size(); ++i) {
        colors[cp[i].i] = cp[i-1].c == cp[i].c ? colors[cp[i-1].i] : colors[cp[i-1].i] + 1;
    }
}

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

int main() {
    int n, m;
    std::cin >> n;
    std::cin >> m;
    std::vector<int> colors(n, 0);
    std::vector<query> queries;
    for(int i = 0; i < n; ++i) {
        std::cin >> colors[i];
    }
    normalize_colors(colors);

    std::vector<tree*> nodes(n, nullptr);
    nodes[0] = new tree(1, colors[0]);
    for(int i = 0; i<n-1; ++i) {
        int u, v;
        std::cin >> u;
        std::cin >> v;
        --u, --v;
        if(nodes[u] != nullptr && nodes[v] != nullptr) {
            nodes[u]->addChild(nodes[v]);
        } else if(nodes[u] != nullptr && nodes[v] == nullptr) {
            nodes[v] = new tree(v+1, colors[v]);
            nodes[u]->addChild(nodes[v]);
        } else if(nodes[u] == nullptr && nodes[v] != nullptr){
            nodes[u] = new tree(u+1, colors[u]);
            nodes[v]->addChild(nodes[u]);
        }
    }

    tree* root = nodes[0];
    std::vector<tree*> lind(n);
    int time = -1;
    linearize_tree(colors, root, lind, time);

    for(int i = 0; i<m; ++i) {
        int v, k;
        std::cin >> v;
        std::cin >> k;

        queries.emplace_back(nodes[v - 1]->f, k, i);
    }

    std::sort(queries.begin(), queries.end(), [](query q1, query q2){
        if(q1.f == q2.f) {
            return q1.k > q2.k;
        } else return q1.f < q2.f;
    });

    int lb = -1;
    std::vector<int> colormap(n, 0), ks(n+1, 0), answ(m, 0);
    for(int i = 0; i<lind.size(); ++i) colormap[lind[i]->c]++;

    for(int i = 0; i<colormap.size(); ++i) ks[colormap[i]]++;
    int sum = 0;
    int old_f = 0, old_l = lind.size() - 1;
    for(int j = ks.size() - 1; j>=queries[0].k; --j) sum+=ks[j];
    int lastk = queries[0].k > n ? n+1 : queries[0].k;
    answ[queries[0].i] = sum;

    for(int i = 1; i<queries.size(); ++i) {
        int cf = queries[i].f, cl = lind[queries[i].f]->l;
        if(cf != old_f) {
            
            while(old_l < cl) {
                int c = lind[++old_l]->c;
                int oldk = colormap[c];
                colormap[c]++;
                ks[colormap[c]]++;
                ks[oldk]--;
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
            if(queries[i].k > n) {
                lastk = n+1;
            } else {
                for(int j = ks.size() - 1; j>=queries[i].k; --j) sum+=ks[j];
                lastk = queries[i].k;
            }
            answ[queries[i].i] = sum;
        } else {
            int ck = queries[i].k;
            if(ck <= n) {
                while(lastk > ck) {
                    sum += ks[--lastk];
                }
            }
            answ[queries[i].i] = sum;
        }
    }
    
    for(int i = 0; i<m; ++i) {
       std::cout << answ[i] << std::endl;
    }
    
}
