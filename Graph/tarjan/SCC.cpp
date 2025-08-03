#include <bits/stdc++.h>

struct SCC {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> stk;
    std::vector<int> dfn, low, bel;
    int cur, cnt;
    
    SCC() = default;
    SCC(int n) { init(n); }
    
    void init(int n) {
        this -> n = n;
        adj.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        bel.assign(n + 1, 0);
        stk.clear();
        cur = cnt = 0;
    }
    
    void add(int u, int v) {
        adj[u].push_back(v);
    }
    
    void tarjan(int u) {
        dfn[u] = low[u] = ++cur;
        stk.push_back(u);
        
        for (auto v : adj[u]) {
            if (dfn[v] == 0) {
                tarjan(v);
                low[u] = std::min(low[u], low[v]);
            } else if (bel[v] == 0) {
                low[u] = std::min(low[u], dfn[v]);
            }
        }
        
        if (dfn[u] == low[u]) {
            int x = cnt++;
            do {
                bel[x = stk.back()] = cnt;
                stk.pop_back();
            } while (x != u);
        }
    }
    
    std::vector<int> work() {
        for (int i = 1; i <= n; i++) {
            if (dfn[i] == 0) tarjan(i);
        }
        return bel;
    }
    
    auto getGraph() {
        work();
        std::vector<std::vector<int>> adj(cnt + 1);
        for (int u = 1; u <= n; ++u) {
            for (auto v : adj[u]) {
                if (bel[u] != bel[v]) {
                    adj[bel[u]].push_back(bel[v]);
                }
            }
        }
        return std::pair { cnt, adj };
    }
};
