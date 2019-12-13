#include <iostream>
#include <vector>
#include <sstream>

struct node{
    int v, c = 0;
    std::vector<node*> next;

    node(int v) : v(v){}
    
    void add(node* n) {
        next.push_back(n);
    }
};

void visit(node* nd) {
    nd->c = 1;
    for(int i = 0; i<nd->next.size(); ++i) {
        if(nd->next[i]->c == 0) {
            visit(nd->next[i]);
        }
    }
}

int count_scc(const std::vector<node*>& graph) {
    int sum = 0;
    for(int i = 0; i<graph.size(); ++i) {
        if(graph[i]->c == 0) {
            visit(graph[i]);
            ++sum;    
        }
    }

    return sum;
} 

int main() {
    int n, m;
    std::cin >> n;
    std::cin >> m;
    std::vector<std::vector<node*>> languages(m+1);
    std::vector<node*> graph(n);
    int nl_sum = 0;
    for(int i = 0; i< n; ++i) {
        node* nd = new node(i);
        graph[i] = nd;
        int nl = 0;
        std::cin >> nl;
        nl_sum += nl;
        for(int j = 0; j<nl; ++j) {
            int x = 0;
            std::cin >> x;
            for(int k=0; k<languages[x].size(); ++k) {
                languages[x][k]->add(nd);
                nd->add(languages[x][k]);
            }
            languages[x].push_back(nd);
        }
    }

    int res = nl_sum == 0 ? n : count_scc(graph) - 1;

    std::cout << res << std::endl;
}
