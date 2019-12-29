#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

struct query{
    int i, j, x, r = 0;

    query(int i, int j, int x) : i(i), j(j), x(x) {}
};

struct node{
    int v;
    node *l, *r;

    node(int v, node *l, node *r) : v(v), l(l), r(r) {}
    node(int v) : node(v, NULL, NULL) {}
};

struct persistent_segtree{
    std::vector<node*> roots;
    int n;

    persistent_segtree(int n) {
        int u = 1, k = 0;
        while(u < n) u = std::pow(2, ++k);
        this->n = u;

        node * root = make_tree(std::vector<int>(u, 0), 0, u-1);
        roots.push_back(root);
    }

    node* make_tree(const std::vector<int> &base, int lb, int rb) {
        if(lb >= rb) {
            return new node(base[lb]);
        }

        int h = (rb - lb) / 2;
        node *ln = make_tree(base, lb, lb + h);
        node *rn = make_tree(base, lb + h + 1, rb);

        node *root = new node(ln->v + rn->v, ln, rn);

        return root;
    }

    node* util_add(int k, int v, node* root, int lb, int rb) {
        if(k < lb || k > rb) {
            return root;
        } else {
            if(lb == rb) {
                return new node(root->v + v);
            } else {
                int h = (rb - lb) / 2;
                node *ln = util_add(k, v, root->l, lb, lb + h);
                node *rn = util_add(k, v, root->r, lb + h + 1, rb);

                return new node(root->v + v, ln, rn);
            }
        }
    }

    void add(int k, int v) {
        node* nroot = util_add(k, v, roots[roots.size() - 1], 0, this->n - 1);
        this->roots.push_back(nroot);
    }

    int util_sum(node *root, int i, int j, int lb, int rb) {
        if(i <= lb && rb <= j) {
            return root->v;
        } else if(j < lb || i > rb) {
            return 0;
        } else {
            int h = (rb - lb) / 2;
            int ls = util_sum(root->l, i, j, lb, lb + h);
            int rs = util_sum(root->r, i, j, lb + h + 1, rb);
            return ls + rs;
        }
    }

    int sum(int t, int i, int j) {
        if(i > j) return 0;
        if(i < 0 || j > this->n - 1) return 0;
        
        return util_sum(roots[++t], i, j, 0, this->n - 1);
    }

    int sum(int t, int k) {
        return sum(t, 0, k);
    }
};

void read_data(std::ifstream &in, int &n, int &m, std::vector<int> &nums, std::vector<query> &qs) {
    in >> n;
    in >> m;
    nums.reserve(n);
    for(int i = 0; i<n; ++i) {
        int x;
        in >> x;
        nums.push_back(x);
    }

    qs.reserve(m);
    for(int k = 0; k<m; ++k) {
        int i, j, x;
        in >> i;
        in >> j; 
        in >> x;
        qs.emplace_back(i, j, x);
    }
}

int main(int argc, char** argv) {
    if(argc < 2) return 1;

    std::ifstream in;
    in.open(argv[1]);

    int n, m;
    std::vector<int> nums;
    std::vector<query> qs;
    read_data(in, n, m, nums, qs);

    in.close();

    persistent_segtree ps(n);
    for(int i = 0; i<nums.size(); ++i) ps.add(nums[i], 1);

    for(int i = 0; i<m; ++i) qs[i].r = ps.sum(qs[i].j, qs[i].x) - (qs[i].i > 0 ? ps.sum(qs[i].i - 1, qs[i].x) : 0);

    for(int i = 0; i<m; ++i) std::cout << qs[i].r << std::endl;
}
