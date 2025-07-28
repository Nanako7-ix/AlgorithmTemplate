#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

#define ls (u << 1)
#define rs (u << 1 | 1)
template<typename Func>
struct SegmentGraph {
    int n;
    std::vector<int> p;
    Func add;
    
    SegmentGraph() = default;
    
    SegmentGraph(int n, Func&& F) : add(F) {
        this -> n = n;
        p.assign(n + 1, 0);
        build(1, 1, n);
    }

    void build(int u, int l, int r) {
        if (l == r) {
            p[l] = u;
            return;
        }
        int m = (l + r) >> 1;
        build(ls, l, m);
        build(rs, m + 1, r);
        add(u, ls), add(u, rs);
    }

    void link(int L, int R, int v, int u, int l, int r) {
        if (L <= l && r <= R) {
            return void(add(p[v], u));
        }
        int m = (l + r) >> 1;
        if (L <= m) link(L, R, v, ls, l, m);
        if (R > m)  link(L, R, v, rs, m + 1, r);
    }

    void link(int v, int l, int r) {
        link(l, r, v, 1, 1, n);
    }
};
#undef ls
#undef rs

struct SCC {
    int n;
    vector<vector<int>> adj;
    vector<int> stk;
    vector<int> dfn, low, bel;
    int cur, cnt;
    
    SCC () = default;
    SCC (int n) { init(n); }
    
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
                low[u] = min(low[u], low[v]);
            } else if (bel[v] == 0) {
                low[u] = min(low[u], dfn[v]);
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
    
    vector<int> work() {
        for (int i = 1; i <= n; i++) {
            if (dfn[i] == 0) tarjan(i);
        }
        return bel;
    }
    
    struct Graph {
        int n;
        vector<vector<int>> adj;
    };
    
    Graph getGraph() {
        work();

        Graph g;
        g.n = cnt;
        g.adj.assign(g.n + 1, {});
        for (int u = 1; u <= n; ++u) {
            for (auto v : adj[u]) {
                if (bel[u] != bel[v]) {
                    g.adj[bel[u]].push_back(bel[v]);
                }
            }
        }
        
        return g;
    }
};

void Thephix() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto check = [&](int k) -> bool {
        // 任意选择的两个点 u, v 需要满足 |u - v| >= v
        // 所以条件为：
        //  u -> ![u + 1. min(u + k - 1, n)]
        //  u -> ![max(1, u - k + 1), u - 1]
        // !u ->  adj[u]
        SCC scc(4 << __lg(2 * n));
        SegmentGraph seg(2 * n, [&](int u, int v) {
            scc.add(u, v);
        });
        auto p = seg.p;
        for (int u = 1; u <= n; ++u) {
            if (u + 1 <= min(u + k - 1, n)) {
                seg.link(u, u + 1 + n, min(u + k - 1, n) + n);
            }
            if (max(1, u - k + 1) <= u - 1) {
                seg.link(u, max(1, u - k + 1) + n, u - 1 + n);
            }
            for (auto v : adj[u]) {
                scc.add(p[u + n], p[v]);
            }
        }
        scc.work();
        for (int u = 1; u <= n; ++u) {
            if (scc.bel[p[u]] == scc.bel[p[u + n]]) {
                return false;
            }
        }
        return true;
    };

    int l = 1, r = n, res = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            res = mid, l = mid + 1;
        } else r = mid - 1;
    }

    assert(res != -1);
    cout << res << "\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}