#include <bits/stdc++.h>

/**
 * ds(dfn(*)) = a(*)
 * ds(*) = a(idfn(*))
 */

struct HLD {
    int n = 0, tot = 0;
    std::vector<std::vector<int>> adj;
    std::vector<int> dfn, idfn, siz, fa, top, dep;
    HLD() = default;
    HLD(int n) { init(n); }
    void init(int n) {
        this -> n = n;
        tot = 0;
        adj.assign(n + 1, {});
        dfn .assign(n + 1, 0);
        idfn.assign(n + 1, 0);
        siz.assign(n + 1, 0);
        fa .assign(n + 1, 0);
        top.assign(n + 1, 0);
        dep.assign(n + 1, 0);
    }
    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int root = 1) {
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if(fa[u] != 0) {
            adj[u].erase(find(adj[u].begin(), adj[u].end(), fa[u]));
        }
        siz[u] = 1;
        for(auto& v : adj[u]) {
            dep[v] = dep[fa[v] = u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if(siz[v] > siz[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    }
    void dfs2(int u) {
        dfn[u] = ++tot;
        idfn[tot] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
    }
    int lca(int u, int v) {
        while(top[u] != top[v]) {
            if(dep[top[u]] > dep[top[v]]) {
                u = fa[top[u]];
            } else {
                v = fa[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    int jump(int u, int k) {
        assert(dep[u] >= k);
        int d = dep[u] - k;
        while(dep[top[u]] > d) {
            u = fa[top[u]];
        }
        return idfn[dfn[u] - dep[u] + d];
    }
    template<typename Func>
    void modify(int u, int v, Func modify) {
        while(top[u] != top[v]) {
            if(dep[top[u]] > dep[top[v]]) {
                modify(dfn[top[u]], dfn[u]);
                u = fa[top[u]];
            } else {
                modify(dfn[top[v]], dfn[v]);
                v = fa[top[v]];
            }
        }
        if(dep[u] < dep[v]) {
            modify(dfn[u], dfn[v]);
        } else modify(dfn[v], dfn[u]);
    }
    template<typename Func>
    void modify(int u, Func modify) {
        modify(dfn[u], dfn[u] + siz[u] - 1);
    }
    template<typename Func, typename T = std::invoke_result_t<Func, int, int>>
    T query(int u, int v, Func query, T res = {}) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                res = query(dfn[top[u]], dfn[u]) + res;
                u = fa[top[u]];
            } else {
                res = query(dfn[top[v]], dfn[v]) + res;
                v = fa[top[v]];
            }
        }
        if (dep[u] < dep[v]) {
            return query(dfn[u], dfn[v]) + res;
        } else {
            return query(dfn[v], dfn[u]) + res;
        }
    }
    template<typename Func, typename T = std::invoke_result_t<Func, int, int>>
    T query(int u, Func query) {
        return query(dfn[u], dfn[u] + siz[u] - 1);
    }
    bool isAncester(int f, int u) {
        return dfn[f] <= dfn[u] && dfn[u] < dfn[f] + siz[f];
    }
    int rootedParent(int rt, int u) {
        if(rt == u) return rt;
        if (!isAncester(u, rt)) return fa[u];
        auto it = std::upper_bound(adj[u].begin(), adj[u].end(), rt, [&](int x, int y) {
            return dfn[x] < dfn[y];
        }) - 1;
        return *it;
    }
    int rootedSize(int rt, int u) {
        if (rt == u) return n;
        if (!isAncester(u, rt)) return siz[u];
        return n - siz[rootedParent(rt, u)];
    }
    int rootedLca(int rt, int u, int v) {
        return lca(rt, u) ^ lca(u, v) ^ lca(v, rt);
    }
};