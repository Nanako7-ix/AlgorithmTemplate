/**
 * Author:  Thephix
 * Created: 2025/06/06 17:08:20
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
using namespace std;

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

std::array<i64, 2> Mod { 224247619,566424149 };
std::array<i64, 2> base { 131,13331 };

struct Hashing {
    static int n;
    static std::array<std::vector<i64>, 2> f;

    static void init (int m) {
        if(m <= n) return;
        f[0].resize(2 * m), f[1].resize(2 * m);

        for (int i = n; i < 2 * m; ++i) {
            f[0][i] = f[0][i - 1] * base[0] % Mod[0];
            f[1][i] = f[1][i - 1] * base[1] % Mod[1];
        }
        n = 2 * m;
    }
    
    static i64 p (int i, int n) {
        init(n + 1);
        return f[i][n];
    }
    
    std::array<std::vector<i64>, 2> h;
    
    Hashing () = default;
    Hashing (const std::string& s) {
        init(s);
    }
    
    void init (const std::string& s) {
        int n = s.size();
        h[0].assign(n + 1, 0);
        h[1].assign(n + 1, 0);
        
        for (int i = 1; i <= n; ++i) {
            h[0][i] = (h[0][i - 1] * base[0] % Mod[0] + s[i - 1]) % Mod[0];
            h[1][i] = (h[1][i - 1] * base[1] % Mod[1] + s[i - 1]) % Mod[1];
        }
    }
    
    std::array<i64, 2> query (int l, int r) {
        l--;
        assert(l < r);
        return {
            (h[0][r] - h[0][l] * p(0, r - l) % Mod[0] + Mod[0]) % Mod[0],
            (h[1][r] - h[1][l] * p(1, r - l) % Mod[1] + Mod[1]) % Mod[1],
        };
    }
};

int Hashing::n = 1;
std::array<std::vector<i64>, 2> Hashing::f {
    std::vector {1LL}, std::vector {1LL}
};

template<typename Func = std::equal_to<char>>
auto Manacher(const std::string& s, Func&& check = Func {}) {
    int n = s.size();
    Hashing hs(s);
    std::vector<int> f(n), ans(n);
    set<array<i64, 2>> S;
    ans[0] = S.insert(hs.query(1, 1)).second;
    for (int i = 0, j = 0; i < n; ++i) {
        f[i] = i < j + f[j] ? std::min(f[2 * j - i], j + f[j] - i) : 1;
        while (i + f[i] < n && i - f[i] >= 0 && check(s[i + f[i]], s[i - f[i]])) ++f[i];
        if (i + f[i] > j + f[j]) {
            for (int k = std::max(i, j + f[j]); k < i + f[i]; ++k) {
                auto [l, r] = std::array { 2 * i - k , k };
                ans[r] += S.insert(hs.query(l + 1, r + 1)).second;
            }
            j = i;
        }
    }
    for (int i = 1; i < n; ++i) {
        ans[i] += ans[i - 1];
    }
    return ans;
}

void solve() {
    int n;
    string s;
    cin >> n >> s;
    vector l(Manacher(s));

    reverse(s.begin(), s.end());
    vector r(Manacher(s));

    i64 p = 1, ans;
    SuffixAutomaton SAM;
    for (int i = 0; i < n - 1; ++i) {
        p = SAM.extend(p, s[i] - 'a');
        ans = max(ans, l[n - i - 2] * (SAM.count() - r[i]));
    }
    cout << ans << "\n";
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