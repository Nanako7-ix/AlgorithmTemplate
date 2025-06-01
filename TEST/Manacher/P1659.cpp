/**
 * Author:  Thephix
 * Created: 2025/05/27 01:55:56
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using i128 = __int128;
using u128 = unsigned __int128;
using lf = double;

std::vector<int> Manacher(const std::string& t) {
    std::string s = "#";
    for (auto c : t) {
        s += c, s += '#';
    }
    int n = s.size();
    std::vector<int> f(n);
    for (int i = 0, j = 0; i < n; ++i) {
        f[i] = i < j + f[j] ? std::min(f[2 * j - i], j + f[j] - i) : 1;
        while (i + f[i] < n && i - f[i] >= 0 && s[i + f[i]] == s[i - f[i]]) ++f[i];
        if (i + f[i] > j + f[j]) j = i;
    }
    return f;
}

std::vector<std::array<int, 2>> prase(const std::vector<int> f) {
    std::vector<std::array<int, 2>> ans;
    for (int i = 0; i < (int) f.size(); ++i) {
        int l = (i - f[i] + 1) / 2;
        int r = (i + f[i]) / 2 - 1;
        if (l <= r) ans.push_back({l, r});
    }
    return ans;
}

i64 power (i64 a, i64 b) {
    i64 res = 1;
    for (a %= 19930726; b; b >>= 1, a = a * a % 19930726) {
        if (b & 1) res = res * a % 19930726;
    } return res;
}

void solve() {
    i64 n, k;
    std::string s;
    std::cin >> n >> k >> s;
    auto f = prase(Manacher(s));

    std::vector<int> a(n + 1);
    for (auto [l, r] : f) {
        a[r - l + 1]++;
    }

    i64 ans = 1;
    for (int i = n; k && i >= 1; --i) {
        if (i > 2) a[i - 2] += a[i];
        if (i % 2 == 0) continue;
        i64 x = std::min<i64>(k, a[i]);
        ans = ans * power(i, x) % 19930726;
        k -= x;
    }

    std::cout << (k ? -1 : ans) << "\n";
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