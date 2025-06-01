/**
 * Author:  Thephix
 * Created: 2025/06/01 17:30:59
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

struct KMP : std::string {
    int n;
    std::vector<int> fail;
    KMP (std::string s) : std::string(s), n(s.size()), fail(n) {
        for (int i = 1, j = 0; i < n; ++i) {
            while (j && s[i] != s[j]) j = fail[j - 1];
            fail[i] = j += (s[i] == s[j]);
        }
    }
};

auto match(std::string s, KMP& p) {
    int n = s.size();
    std::vector<std::array<int, 2>> ans;
    for (int i = 0, j = 0; i < n; ++i) {
        while (j && s[i] != p[j]) j = p.fail[j - 1];
        j += (s[i] == p[j]);
        if (j == p.n) {
            ans.push_back({i - j + 1, j});
            j = p.fail[j - 1];
        }
    }
    return ans;
}

void solve() {
    std::string s, p;
    std::cin >> s >> p;
    KMP kmp(p);
    auto f = match(s, kmp);
    for (auto [l, r] : f) std::cout << l + 1 << "\n";
    for (int i = 0; i < (int) p.size(); ++i) {
        std::cout << kmp.fail[i] << " \n"[i == (int) p.size() - 1];
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