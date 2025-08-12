#include <bits/stdc++.h>

struct VDCC {
    int n, cur;
    std::vector<std::vector<int>> adj, vdcc;
    std::vector<int> dfn, low, stk;

    std::vector<int> cut;

    VDCC (int n = 0) {
        init(n);
    }

    void init(int n) {
        this -> n = n;
        cur = 0;
        adj.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        cut.assign(n + 1, 0);
        vdcc.clear();
        stk.clear();
    }

    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void tarjan(int u, int fa) {
        int child = 0;
        stk.push_back(u);
        low[u] = dfn[u] = ++cur;
        for (auto v : adj[u]) {
            if (!dfn[v]) {
                child++;
                tarjan(v, u);
                low[u] = std::min(low[u], low[v]);
                if(low[v] >= dfn[u]) {
                    if (fa == 0) {
                        cut[u] = 1;
                    }
                    std::vector<int> component {u};
                    int x;
                    do {
                        x = stk.back();
                        stk.pop_back();
                        component.push_back(x);
                    } while(x != v);

                    vdcc.push_back(component);
                }
            } else if (v != fa) {
                low[u] = std::min(low[u], dfn[v]);
            }
        }

        if (fa == 0 && child == 0) {
            vdcc[u].push_back(vdcc.size());
            vdcc.push_back({u});
        }

        if (fa == 0 && child >= 2) {
            cut[u] = 1;
        }
    }

    void work() {
        for (int i = 1; i <= n; ++i) {
            if (!dfn[i]) tarjan(i, 0);
        }
    }

    struct Graph {
        int n, m;
        vector<vector<int>> adj;
    };
    
    std::tuple<int, int>  getTree() {
        work();
        Graph G;
        G.n = n, G.m = vdcc.size();
        G.adj.assign(G.n + G.m + 1, {});
        for (int i = 1; i <= G.m; ++i) {
            for (auto x : vdcc[i - 1]) {
                G.adj[x].push_back(i + G.n);
                G.adj[i + G.n].push_back(x);
            }
        }
        return G;
    }
};