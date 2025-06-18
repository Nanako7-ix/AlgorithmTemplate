/**
 *
 *  $$$$$$\  $$$$$$\  $$$$$$\  $$\       $$\       $$$$$$\  
 * $$  __$$\ \_$$  _|$$  __$$\ $$ |      $$ |     $$  __$$\ 
 * $$ /  \__|  $$ |  $$ /  $$ |$$ |      $$ |     $$ /  $$ |
 * $$ |        $$ |  $$$$$$$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |        $$ |  $$  __$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |  $$\   $$ |  $$ |  $$ |$$ |      $$ |     $$ |  $$ |
 *  $$$$$$ | $$$$$$\ $$ |  $$ |$$$$$$$$\ $$$$$$$$\ $$$$$$  |
 * \______/  \______|\__|  \__|\________|\________|\______/ 
 *
 * Author:  Nanako7_ix
 * Created: 2025/06/11 09:13:02
 * 好想和 めぐる 一起打 xcpc 啊
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define setpre(x) fixed << setprecision(x)
#define debug(x) cerr << #x << " = " << x << "\n"
#define endl "\n"
using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64 = double;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

struct SuffixAutomaton {
    static constexpr int N = 26;
    struct Node {
        int len;
        int link;
        std::array<int, N> next;
        Node() : len(), link(), next() {}
    };

    i64 substr;
    std::vector<Node> t;

    SuffixAutomaton () { init(); }

    void init() {
        t.assign(2, Node {});
        t[0].next.fill(1);
        t[0].len = -1;
        substr = 0;
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
        substr += t[cur].len - t[t[cur].link].len;
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

    i64 count () {
        return substr;
    }
};

struct Null { void operator()(int l, int r) {} };

template<typename F>
std::vector<int> Manacher(const std::string& t, F&& op1) {
    std::string s = "#";
    for (auto c : t) s += c, s += '#';

    int n = s.size();
    std::vector<int> f(n);
    for (int i = 0, j = 0; i < n; ++i) {
        f[i] = i < j + f[j] ? std::min(f[2 * j - i], j + f[j] - i) : 1;
        while (i + f[i] < n && i - f[i] >= 0 && s[i + f[i]] == s[i - f[i]]) ++f[i];
        if (i + f[i] > j + f[j]) {
            for (int k = std::max(i, j + f[j]); k < i + f[i]; ++k) {
                if (s[k] != '#') continue;
                op1(i - k / 2 + 1 , (k - 1) / 2 + 1);
            }
            j = i;
        }
    }
    return f;
}

void solve() {
    string s;
    cin >> s;
    int n = s.size(), p = 1;
    SuffixAutomaton sam;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        p = sam.extend(p, s[i - 1] - 'a');
        a[i] = p;
    }
    
    int m = sam.size() - 1;
    vector<int> dp(m + 1);
    vector fa(__lg(m) + 1, vector<int> (m + 1));
    for (int i = 1; i <= n; ++i) {
        dp[a[i]]++;
    }

    vector<int> deg(m + 1);
    queue<int> q;
    for (int u = 1; u <= m; ++u) {
        fa[0][u] = sam.link(u);
        deg[fa[0][u]]++;
    }
    for (int i = 1; i <= m; ++i) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int v = fa[0][u];
        dp[v] += dp[u];
        deg[v]--;
        if (deg[v] == 0) {
            q.push(v);
        }
    }

    for (int i = 1; i <= __lg(m); ++i) {
        for (int u = 1; u <= m; ++u) {
            fa[i][u] = fa[i - 1][fa[i - 1][u]];
        }
    }

    i64 ans = 0;
    Manacher(s, [&](int l, int r) {
        int len = r - l + 1, u = a[r];
        for (int i = __lg(m); i >= 0; --i) {
            int v = fa[i][u];
            if (sam.len(v) >= len) {
                u = v;
            }
        }
        ans = max(ans, 1LL * dp[u] * len);
    });
    cout << ans << "\n";
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}