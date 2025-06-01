/**
 * Author:  Thephix
 * Created: 2025/05/29 13:32:24
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using i128 = __int128;
using u128 = unsigned __int128;
using f64 = double;
using f128 = __float128;

struct AhoCorasick {
    static constexpr int N = 26;
    struct Node {
        int len, fail;
        std::vector<int> adj;
        std::array<int, N> next;
        Node() : len(0), fail(0), adj{}, next{} {}
    };

    std::vector<Node> t;

    AhoCorasick() { init(); }
    
    void init() {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
        t[0].adj.push_back(1);
    }
    
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    
    int insert(const std::string& s) {
        int p = 1;
        for (auto c : s) {
            int x = c - 'a';
            if (t[p].next[x] == 0) {
                t[p].next[x] = newNode();
                t[t[p].next[x]].len = t[p].len + 1;
            }
            p = t[p].next[x];
        }
        return p;
    }
    
    void work() {
        std::queue<int> q;
        q.push(1);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int i = 0; i < N; i++) {
                if (t[u].next[i] == 0) {
                    t[u].next[i] = t[t[u].fail].next[i];
                } else {
                    t[t[u].next[i]].fail = t[t[u].fail].next[i];
                    t[t[t[u].fail].next[i]].adj.push_back(t[u].next[i]);
                    q.push(t[u].next[i]);
                }
            }
        }
    }
    
    int len(int p) {
        return t[p].len;
    }
    
    int fail(int p) {
        return t[p].fail;
    }
    
    const std::vector<int>& adj(int p) {
        return t[p].adj;
    }
    
    int next(int p, int x) {
        return t[p].next[x];
    }
    
    int size() {
        return t.size();
    }
};

template<typename Info>
struct SegmentTree {
    int n, cnt;
    std::vector<Info> info;
    std::vector<int> ls, rs, ver;
    
    SegmentTree() = default;
    SegmentTree(int n, int m) {
        init(n, m);
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    SegmentTree(const Iterator& l, const Iterator& r, int m) {
        init(l, r, m);
    }

    void init(int n, int m) {
        std::vector<Info> _(n, Info{});
        init(_.begin(), _.end(), m);
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    void init(const Iterator& l, const Iterator& r, int m) {
        n = r - l;
        cnt = 0;
        int N = (n + m) << 5;
        ver.assign(m + 1, 0);
        ls.assign(N, 0);
        rs.assign(N, 0);
        info.assign(N, Info{});
        build(ver[0], 1, n, l);
    }

    void pull(int u) {
        info[u] = info[ls[u]] + info[rs[u]];
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    void build(int& u, int l, int r, const Iterator& it) {
        if(u == 0) u = ++cnt;
        if(l == r) {
            info[u] = *it;
            return;
        }
        int m = (l + r) >> 1;
        build(ls[u], l, m, it);
        build(rs[u], m + 1, r, it + (m - l + 1));
        pull(u);
    }

    template<typename Func>
    void modify(int p, Func&& op, int& u, int v, int l, int r) {
        u = ++cnt;
        ls[u] = ls[v], rs[u] = rs[v];
        if (l == r) {
            info[u] = info[v];
            op(info[u]);
            return;
        }
        int m = (l + r) >> 1;
        if (p <= m) modify(p, op, ls[u], ls[v], l, m);
        else modify(p, op, rs[u], rs[v], m + 1, r);
        pull(u);
    }

    template<typename Func>
    void modify(int v, int u, int p, Func&& op) {
        modify(p, op, ver[u], ver[v], 1, n);
    }

    Info query(int L, int R, int x, int y, int l, int r) {
        if (L <= l && r <= R) {
            return info[y] - info[x];
        }
        int m = (l + r) >> 1;
        if (R <= m) return query(L, R, ls[x], ls[y], l, m);
        if (L > m)  return query(L, R, rs[x], rs[y], m + 1, r);
        return query(L, R, ls[x], ls[y], l, m) + query(L, R, rs[x], rs[y], m + 1, r);
    }

    Info query(int x, int y, int l, int r) {
        assert(x <= y && l <= r);
        return query(l, r, ver[x], ver[y], 1, n);
    }

    Info query(int L, int R, int u, int l, int r) {
        if (L <= l && r <= R) {
            return info[u];
        }
        int m = (l + r) >> 1;
        if (R <= m) return query(L, R, ls[u], l, m);
        if (L > m)  return query(L, R, rs[u], m + 1, r);
        return query(L, R, ls[u], l, m) + query(L, R, rs[u], m + 1, r);
    }

    Info query(int u, int l, int r) {
        return query(l, r, ver[u], 1, n);
    }
};

void solve() {
    int n, q, len = 0;
    std::cin >> n >> q;

    AhoCorasick ac;
    std::vector<std::string> a(n + 1);
    std::vector<int> node(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        node[i] = ac.insert(a[i]);
        len += a[i].size();
    }
    ac.work();
    
    int m = ac.size() - 1, cur = 0;
    std::vector<int> dfn(m + 1), siz(m + 1);
    [&](this auto&& dfs, int u) -> int {
        siz[u] = 1, dfn[u] = ++cur;
        for (auto v : ac.adj(u)) {
            siz[u] += dfs(v);
        }
        return siz[u];
    } (1);

    int cnt = 0;
    std::vector<int> ver(n + 1);
    SegmentTree<int> seg(m, len);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0, p = 1; j < (int) a[i].size(); ++j) {
            cnt++, p = ac.next(p, a[i][j] - 'a');
            seg.modify(cnt - 1, cnt, dfn[p], [](int& info) {
                info++;
            });
        }
        ver[i] = cnt;
    }

    for (int i = 1; i <= q; ++i) {
        int l, r, u;
        std::cin >> l >> r >> u;
        u = node[u];
        std::cout << seg.query(ver[l - 1], ver[r], dfn[u], dfn[u] + siz[u] - 1) << "\n";
    }
}

signed main() {
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int T = 1;
    // std::cin >> T;

    while (T--) {
        solve ();
    }

    return 0;
}