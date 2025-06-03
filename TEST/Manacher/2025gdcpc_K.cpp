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

struct kmpAlgorithm : std::string {
    int n;
    std::vector<int> fail;
    kmpAlgorithm (std::string s) : std::string(s), n(s.size()), fail(n) {
        for (int i = 1, j = 0; i < n; ++i) {
            while (j && s[i] != s[j]) j = fail[j - 1];
            fail[i] = j += (s[i] == s[j]);
        }
    }
};

auto match(std::string s, kmpAlgorithm& p) {
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

auto Manacher(const std::string& t, char wildcard = '*') {
    std::string s = "#";
    for (auto c : t) {
        s += c, s += '#';
    }

    auto check = [&](char x, char y) {
        return x == y || x == wildcard || y == wildcard;
    };

    int n = s.size(), m = t.size();
    std::vector<int> f(n);
    std::vector<std::array<int, 2>> a;
    for (int i = 0, j = 0; i < n; ++i) {
        f[i] = i < j + f[j] ? std::min(f[2 * j - i], j + f[j] - i) : 1;
        while (i + f[i] < n && i - f[i] >= 0 && check(s[i + f[i]], s[i - f[i]])) ++f[i];
        if (i + f[i] > j + f[j]) j = i;
        auto [l, r] = std::array { (i - f[i] + 1) / 2, (i + f[i]) / 2 - 1 };
        if (l > r || (r - l + 1) % 2 == 0) continue;
        a.push_back({(l + r) >> 1, r});
    }

    std::vector<int> ans(m, 0x3f3f3f3f);
    std::ranges::sort(a);
    for (int i = 0, j = 0; i < (int) a.size(); ++i) {
        auto [m, r] = a[i];
        for (; j <= r; ++j) ans[j] = min(ans[j], m);
    }
    return ans;
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    auto fail = kmpAlgorithm(s).fail;
    auto f = Manacher(s);

    i64 ans = 1;
    for (int i = 1, j = 0; i < n; ++i) {
        while (j && s[i] != s[j]) j = fail[j - 1];
        j += s[i] == s[j];
        if (i == j) {
            ans ^= i + 1;
        } else{
            while (j && 2 * f[i + 1 - j] != i + 1 - j) j = fail[j - 1];
            if (j == 0) ans ^= 1LL * (f[i] + 1);
            else ans ^= 1LL * ((i - j + 1) / 2 + 1);
        }
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