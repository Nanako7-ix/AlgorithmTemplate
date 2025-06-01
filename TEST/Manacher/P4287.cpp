/**
 * Author:  Thephix
 * Created: 2025/05/27 22:46:13
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

int Manacher(const std::string& t) {
    std::string s = "#";
    for (auto c : t) {
        s += c, s += '#';
    }

    int n = s.size(), ans = 0;
    std::vector<int> f(n);
    for (int i = 0, j = 0; i < n; ++i) {
        f[i] = i < j + f[j] ? std::min(f[2 * j - i], j + f[j] - i) : 1;
        while (i + f[i] < n && i - f[i] >= 0 && s[i + f[i]] == s[i - f[i]]) ++f[i];
        if (i + f[i] > j + f[j]) {
            for (int k = std::max(i, j + f[j]); k < i + f[i]; ++k) {
                auto [l, r] = std::array { 2 * i - k , k };
                if (l % 2 == 1 || r % 2 == 1) continue;

                int x = (l + r) >> 1, y = (l + x) >> 1;
                if (s[x] == '#' && s[y] == '#' && y + f[y] > x) {
                    ans = std::max(ans, r - l + 1);
                }
            }
            j = i;
        }
    }

    return ans / 2;
}

void solve() {
    int n;
    std::string s;
    std::cin >> n >> s;
    std::cout << Manacher(s) << "\n";
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