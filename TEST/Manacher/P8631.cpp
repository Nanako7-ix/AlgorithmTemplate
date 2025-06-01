/**
 * Author:  Thephix
 * Created: 2025/05/28 17:56:55
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

auto Manacher(const std::string& t) {
    Hashing hs(t);

    std::string s = "#";
    for (auto c : t) {
        s += c, s += '#';
    }

    int n = s.size(), m = t.size();
    std::vector<int> f(n), ans(m + 1);
    std::set<std::array<i64, 2>> S; 
    for (int i = 0, j = 0; i < n; ++i) {
        f[i] = i < j + f[j] ? std::min(f[2 * j - i], j + f[j] - i) : 1;
        while (i + f[i] < n && i - f[i] >= 0 && s[i + f[i]] == s[i - f[i]]) ++f[i];
        if (i + f[i] > j + f[j]) {
            for (int k = std::max(i, j + f[j]); k < i + f[i]; ++k) {
                if (s[k] != '#') continue;
                auto [l, r] = std::array { i - k / 2 , (k - 1) / 2 };
                if ((r - l + 1) % 2 == 1) continue;
                ans[r + 1] += S.insert(hs.query(l + 1, r + 1)).second;
            }
            j = i;
        }
    }
    for (int i = 1; i <= m; ++i) {
        ans[i] += ans[i - 1];
    }
    return ans;
}

void solve() {
    int n;
    std::string s;
    std::cin >> n >> s;

    auto l = Manacher(s);
    std::reverse(s.begin(), s.end());
    auto r = Manacher(s);

    for (int i = 1; i <= n; ++i) {
        std::cout << l[i] << " \n"[i == n];
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