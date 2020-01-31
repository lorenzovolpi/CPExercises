#include <iostream>
#include <vector>
#include <algorithm>

/*
    The solution to this problem is found using dynamic programming on
    trees. At each node, we can choose if we want to take the current node
    or not. If we take it we sum the cover computed con chilren. If we do 
    not take it we must add 1 for each children and then summ covers of all 
    grandchildren.
*/

struct edge{
    int v1, v2;

    edge(int v1, int v2) : v1(v1), v2(v2) {}
};

struct treeset
{
    int value;
    std::vector<treeset*> children;
    int cover = 0;

    treeset(int v) : value(v) {}

    bool insert(int p, int v) {
        bool res = false;
        if(this->value == p) {
            this->children.push_back(new treeset(v));
            res = true;
        }
        else {
            for(int i = 0; i<children.size(); ++i) {
                res = res || children[i]->insert(p, v);
                if(res) break;
            }
        }

        return res;
    }

    bool insert(edge e) {
        return this->insert(e.v1, e.v2);
    }

    static treeset* buildTree(const std::vector<edge>& edges) {
        if(edges.empty()) return NULL;

        treeset* root = new treeset(edges[0].v1);
        for(int i = 0; i<edges.size(); ++i) root->insert(edges[i]);

        return root;
    }

    void vertexCover() {
        if(children.empty()) return;

        int tm = 1, tnm = 0;
        for(int i = 0; i<children.size(); ++i) {
            children[i]->vertexCover();
            tm += children[i]->cover;
            tnm += 1;
            for(int j = 0; j<children[i]->children.size(); ++j) tnm += children[i]->children[j]->cover;
        } 

        this->cover = std::min(tm, tnm);
    }

};

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<edge> edges;
    edges.reserve(n);

    for(int i = 0; i<n-1; ++i) {
        int p, v;
        std::cin >> p;
        std::cin >> v;

        edges.emplace_back(p, v);
    }

    treeset* root = treeset::buildTree(edges);
    root->vertexCover();
    std::cout << root->cover << std::endl;
}