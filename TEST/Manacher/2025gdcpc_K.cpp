/**
 * Author:  Thephix
 * Created: 2025/06/03 16:12:28
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

auto Manacher(const std::string& s, char wildcard = '*') {
    auto check = [&](char x, char y) {
        return x == y || x == wildcard || y == wildcard;
    };

    int n = s.size();
    std::vector<int> f(n), ans(n, 0);
    for (int i = 0, j = 0; i < n; ++i) {
        f[i] = i < j + f[j] ? std::min(f[2 * j - i], j + f[j] - i) : 1;
        while (i + f[i] < n && i - f[i] >= 0 && check(s[i + f[i]], s[i - f[i]])) ++f[i];
        if (i + f[i] > j + f[j]) {
            for (int k = std::max(i, j + f[j]); k < i + f[i]; ++k) {
                auto [l, r] = std::array { 2 * i - k , k };
                if (l > r) continue;
                ans[r] = (l + r) >> 1;
            }
            j = i;
        }
    }
    return ans;
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector f = Manacher(s);
    vector<int> fail(n);
    for (int i = 1, j = 0; i < n; ++i) {
        while (j && s[i] != s[j]) j = fail[j - 1];
        fail[i] = j += (s[i] == s[j]);
    }

    i64 ans = 1;
    for (int i = 1, j = 0; i < n; ++i) {
        while (j && s[i] != s[j]) j = fail[j - 1];
        j += s[i] == s[j];
        if (i == j) {
            ans ^= i + 1;
            continue;
        }
        while (j && 2 * f[i + 1 - j] != i + 1 - j) j = fail[j - 1];
        if (j == 0) ans ^= 1LL * (i + 1) * (f[i] + 1);
        else ans ^= 1LL * (i + 1) * ((i - j + 1) / 2 + 1);
    }
    cout << ans << "\n";
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