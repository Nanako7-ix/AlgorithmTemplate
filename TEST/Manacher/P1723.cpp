/**
 * Author:  Thephix
 * Created: 2025/05/27 23:56:19
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

auto Manacher(const std::string& t) {
    std::string s = "#";
    for (auto c : t) {
        s += c, s += '#';
    }
    int n = s.size();
    std::vector<int> f(n);
    for (int i = 0, j = 0; i < n; ++i) {
        f[i] = i < j + f[j] ? std::min(f[2 * j - i], j + f[j] - i) : 1;
        while (i + f[i] < n && i - f[i] >= 0 && s[i + f[i]] == s[i - f[i]]) ++f[i];
        if (i + f[i] > j + f[j]) {
            for (int k = std::max(i, j + f[j]); k < i + f[i]; ++k) {
                auto [l, r] = std::array { i - k / 2 , (k - 1) / 2 };
                if (l % 2 == 1 || r % 2 == 1) continue;
            }
            j = i;
        }
        auto [l, r] = std::array { (i + f[i] + 1) / 2, (i - f[i]) / 2 - 1 };
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = std::max(ans, f[i] - 1);
    }
    return ans;
}

void solve() {
    std::string s;
    std::cin >> s;
    std::cout << Manacher(s) << "\n";
}

signed main() {
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int T = 1;
    std::cin >> T;

    while (T--) {
        solve ();
    }

    return 0;
}