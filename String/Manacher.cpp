#include <bits/stdc++.h>

template<typename F, typename G>
std::vector<int> Manacher(const std::string& t, F&& f, G&& g) {
    std::string s = "#";
    for (auto c : t) s += c, s += '#';

    int n = s.size();
    std::vector<int> d(n);
    for (int i = 0, j = 0; i < n; ++i) {
        d[i] = i < j + d[j] ? std::min(d[2 * j - i], j + d[j] - i) : 1;
        while (i + d[i] < n && i - d[i] >= 0 && s[i + d[i]] == s[i - d[i]]) ++d[i];
        if (i + d[i] > j + d[j]) {
            for (int k = std::max(i, j + d[j]); k < i + d[i]; ++k) {
                if (s[k] != '#') continue;
                f(i - k / 2 + 1 , (k - 1) / 2 + 1);
            }
            j = i;
        }
        auto [l, r] = std::array { (i - d[i] + 1) / 2, (i + d[i]) / 2 - 1 };
        if (l <= r) g(l + 1, r + 1);
    }
    return d;
}

template<typename Func>
std::vector<int> Manacher(int n, Func&& op, const int def = '#') {
    n = n << 1 | 1;
    std::vector<int> s(n + 1);
    for (int i = 1; i <= n; ++i) {
        s[i] = i % 2 == 1 ? def : op(i / 2);
    }

    std::vector<int> d(n + 1);
    for (int i = 1, j = 1; i <= n; ++i) {
        d[i] = i < j + d[j] ? std::min(d[2 * j - i], j + d[j] - i) : 1;
        while (i + d[i] <= n && i - d[i] >= 1 && s[i + d[i]] == s[i - d[i]]) ++d[i];
        if (i + d[i] > j + d[j]) j = i;
    }
    return d;
}