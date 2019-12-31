#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using iterator = std::vector<int>::const_iterator;

struct node{
    node *l, *r;
    int t = 0;
    int* it;

    node(node *l, node *r, int* it) : l(l), r(r), it(it) {}
};

struct cptree{
    node *root;
    int n;

    cptree(std::vector<int> &A, std::vector<int> &B) {
        int u = 1, k = 0;
        while(u < B.size()) u = std::pow(2, ++k);
        A.resize(u, 0);
        B.resize(u, 0);
        this->n = u;

        root = make_tree(&B[0], 0, u-1);
    }

    node* make_tree(int* bit, int lb, int rb) {
        if(lb == rb) return new node(NULL, NULL, bit + lb);

        int h = (rb - lb) / 2;
        node *ln = make_tree(bit, lb, lb + h);
        node *rn = make_tree(bit, lb + h + 1, rb);

        return new node(ln, rn, bit + lb);
    }

    void util_copy(int t, node* root, int i, int j, int lb, int rb, int* ait) {
        if(i <= lb && rb <= j) {
            root->it = ait + (lb - i);
            root->t = t;
        } else if(i > rb || j < lb) {
            return;
        } else {
            int h = (rb - lb) / 2;
            util_copy(t, root->l, i, j, lb, lb + h, ait);
            util_copy(t, root->r, i, j, lb + h + 1, rb, ait);
        }
    }

    void copy(int t, int i, int j, int* ait) {
        if( i > j) return;
        if( i < 0 || j >= this->n) return;
        util_copy(t, this->root, i, j, 0, this->n - 1, ait);
    }

    void util_read(node *root, int k, int lb, int rb, int &val, int &lastt) {
        if(lb <= k && k <= rb) {
            if(root->t > lastt) {
                val = *(root->it + (k - lb));
                lastt = root->t;
            }
            if(lb < rb) {
                int h = (rb - lb) / 2;
                util_read(root->l, k, lb, lb + h, val, lastt);
                util_read(root->r, k, lb + h + 1, rb, val, lastt);
            }
        }
    }

    int read(int k) {
        int val = 0;
        int lastt = -1;
        util_read(this->root, k, 0, this->n - 1, val, lastt);
        return val;
    }

};

int main(int argc, char** argv) {
    if(argc < 2) return 1;

    std::ifstream in;
    in.open(argv[1]);

    int n, m;
    in >> n;
    in >> m;
    
    std::vector<int> A(n), B(n);
    for(int i = 0; i<n; ++i) {
        int x;
        in >> x;
        A[i] = x;
    }
    for(int i = 0; i<n; ++i) {
        int x;
        in >> x;
        B[i] = x;
    }

    cptree cp(A, B);
    std::vector<int> results;
    int t = 0;
    for(int i = 0; i<m; ++i) {
        int type;
        in >> type;
        if(type == 1) {
            int x, y, k;
            in >> x; in >> y; in >> k;
            cp.copy(++t, y, y + k - 1, &A[0] + x);
        } else if(type == 2) {
            int k;
            in >> k;
            results.push_back(cp.read(k));
        }
    }

    in.close();

    for(int i = 0; i<results.size(); ++i) std::cout << results[i] << std::endl;
}
