/**
 * Author:  Thephix
 * Created: 2025/05/29 00:33:29
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
    static constexpr int SIGMA = 26;
    struct Node {
        int len, fail;
        std::vector<int> adj;
        std::array<int, SIGMA> next;
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
            
            for (int i = 0; i < SIGMA; i++) {
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

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> node(n);
    AhoCorasick ac;
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        node[i] = ac.insert(s);
    }

    ac.work();
    
    std::string t;
    std::cin >> t;
    int m = ac.size() - 1;
    std::vector<int> dp(m + 1);
    for (int i = 0, p = 1; i < (int) t.size(); ++i) {
        p = ac.next(p, t[i] - 'a');
        dp[p]++;
    }
    
    auto dfs = [&](auto &&dfs, int u) -> int {
        for (auto v : ac.adj(u)) {
            dp[u] += dfs(dfs, v);
        }
        return dp[u];
    };
    dfs(dfs, 1);

    for (int i = 0; i < n; ++i) {
        std::cout << dp[node[i]] << "\n";
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