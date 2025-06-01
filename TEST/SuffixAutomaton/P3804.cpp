/**
 * Author:  Thephix
 * Created: 2025/05/30 17:27:08
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

struct SAM {
    static constexpr int N = 26;
    struct Node {
        int len;
        int link;
        std::array<int, N> next;
        Node() : len(), link(), next() {}
    };

    std::vector<Node> t;

    SAM () { init(); }

    void init() {
        t.assign(2, Node {});
        t[0].next.fill(1);
        t[0].len = -1;
    }

    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }

    int extend(int p, int c) {
        if (t[p].next[c]) {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1) {
                return q;
            }
            int r = newNode();
            t[r].len = t[p].len + 1;
            t[r].link = t[q].link;
            t[r].next = t[q].next;
            t[q].link = r;
            while (t[p].next[c] == q) {
                t[p].next[c] = r;
                p = t[p].link;
            }
            return r;
        }
    
        int cur = newNode();
        t[cur].len = t[p].len + 1;
        while (!t[p].next[c]) {
            t[p].next[c] = cur;
            p = t[p].link;
        }
    
        t[cur].link = extend(p, c);
        return cur;
    }

    int len(int p) {
        return t[p].len;
    }

    int link(int p) {
        return t[p].link;
    }

    int next(int p, int x) {
        return t[p].next[x];
    }
    
    int size() {
        return t.size();
    }
};

void solve() {
    SAM sam;
    std::string s;
    std::cin >> s;

    int p = 1;
    for (auto c : s) {
        p = sam.extend(p, c - 'a');
    }

    int m = sam.size() - 1;
    std::vector<int> siz(m + 1);
    p = 1;
    for (auto c : s) {
        p = sam.next(p, c - 'a');
        siz[p] += 1;
    }

    i64 ans = 0;
    std::vector<std::vector<int>> adj(m + 1);
    for (int i = 2; i <= m; ++i) {
        adj[sam.link(i)].push_back(i);
    }

    auto dfs = [&](auto dfs, int u) -> void {
        for (auto v : adj[u]) {
            dfs(dfs, v);
            siz[u] += siz[v];
        }
        if (siz[u] > 1) {
            ans = std::max(ans, 1LL * sam.len(u) * siz[u]);
        }
    };
    dfs(dfs, 1);
    std::cout << ans << "\n";
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