#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

struct end_vert{
    int i, e;

    end_vert(int i, int e) : i(i), e(e) {}
};

/*
    The problem is solved first computing all SCCs on the input
    direct graph in linear time over the graph with the algorithm seen
    during lessons. Then for each SCC the verteces with minumum value and
    their multiplicity are computed and the sum of all the minima and
    the product of all the multiplicities are given in output. The algorithm
    runs in linear time over the graph.
*/

struct graph{
    std::vector<std::vector<int>> G;
    std::vector<std::vector<int>> GT;
    std::vector<int> weight;
    std::vector<int> start;
    std::vector<int> end;
    int n;

    graph(int n) : n(n) {
        for(int i = 0; i<n; ++i) {
            G.push_back(std::vector<int>(n, 0));
            GT.push_back(std::vector<int>(n, 0));
        }
        weight.resize(n, 0);
        start.resize(n, -1);
        end.resize(n, -1);
    }

    void addEdge(int u, int v) {
        G[u][v] = 1;
        GT[v][u] = 1;
    }

};

void dfs_visit(graph& g, std::vector<int>& color, int& time, int i) {
    color[i] = 1;
    g.start[i] = ++time;
    
    for(int j = 0; j<g.n; ++j) {
        if(g.G[i][j] == 1 && color[j] == 0) {
            dfs_visit(g, color, time, j);
        }
    }

    color[i] = 2;
    g.end[i] = ++time;
}

void dfs(graph& g) {
    std::vector<int> color(g.n, 0);
    int time = -1;
    for(int i = 0; i<g.n; ++i) {
        if(color[i] == 0) {
            dfs_visit(g, color, time, i);
        }
    }
}

void dfst_visit(graph& g, std::vector<int>& color, std::vector<std::vector<int>>& scc, int sccn, int i) {
    color[i] = 1;
    scc[sccn].push_back(i);
    
    for(int j = 0; j<g.n; ++j) {
        if(g.GT[i][j] == 1 && color[j] == 0) {
            dfst_visit(g, color, scc, sccn, j);
        }
    }

    color[i] = 2;
}

std::vector<std::vector<int>> dfst(graph& g, std::vector<int> vs) {
    std::vector<std::vector<int>> scc;
    int sccn = 0;
    std::vector<int> color(g.n, 0);
    for(int j = 0; j<vs.size(); ++j) {
        int i = vs[j];
        if(color[i] == 0) {
            scc.push_back(std::vector<int>());
            dfst_visit(g, color, scc, sccn, i);
            ++sccn;
        }
    }

    return scc;
}

int main() {
    int n;
    std::cin >> n;
    graph g(n);
    for(int i = 0; i<n; ++i) {
        int w;
        std::cin >> w;
        g.weight[i] = w;
    }
    int m;
    std::cin >> m;
    for(int i = 0; i<m; ++i) {
        int u, v;
        std::cin >> u;
        std::cin >> v;
        g.addEdge(u-1, v-1);
    }

    dfs(g);
    std::vector<end_vert> evs;
    for(int i = 0; i<g.n; ++i) {
        evs.emplace_back(i, g.end[i]);
    }

    std::sort(evs.begin(), evs.end(), [](end_vert ev1, end_vert ev2) {
        return ev1.e > ev2.e;
    });

    std::vector<int> vs;
    for(int i = 0; i<n; ++i) vs.push_back(evs[i].i);

    std::vector<std::vector<int>> scc = dfst(g, vs);

    long long min = 0;
    std::vector<int> nows(scc.size(), 0);
    for(int i = 0; i<scc.size(); ++i) {
        int m = INT_MAX;
        for(int j = 0; j<scc[i].size(); ++j) {
            if(g.weight[scc[i][j]] < m) {
                m = g.weight[scc[i][j]];
                nows[i] = 1;
            } else if(g.weight[scc[i][j]] == m) nows[i]++;
        }
        min += m;
    }

    int now = nows[0];
    for(int i = 1; i<nows.size(); ++i) now *= nows[i];

    std::cout << min << " " << (now % 1000000007) << std::endl;

}
