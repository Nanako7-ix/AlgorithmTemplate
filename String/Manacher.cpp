#include <bits/stdc++.h>

template<typename Func = std::equal_to<char>>
auto Manacher(const std::string& t, Func check) {
    std::string s = "#";
    for (auto c : t) {
        s += c, s += '#';
    }

    int n = s.size();
    std::vector<int> f(n);
    for (int i = 0, j = 0; i < n; ++i) {
        f[i] = i < j + f[j] ? std::min(f[2 * j - i], j + f[j] - i) : 1;
        while (i + f[i] < n && i - f[i] >= 0 && check(s[i + f[i]], s[i - f[i]])) ++f[i];
        if (i + f[i] > j + f[j]) {
            for (int k = std::max(i, j + f[j]); k < i + f[i]; ++k) {
                if (s[k] != '#') continue;
                auto [l, r] = std::array { i - k / 2 , (k - 1) / 2 };
            }
            j = i;
        }
        auto [l, r] = std::array { (i - f[i] + 1) / 2, (i + f[i]) / 2 - 1 };
        if (l > r) continue;
    }
}

template<typename Func = std::equal_to<char>>
auto Manacher(const std::string& s, Func&& check = Func {}) {
    int n = s.size();
    std::vector<int> f(n);
    for (int i = 0, j = 0; i < n; ++i) {
        f[i] = i < j + f[j] ? std::min(f[2 * j - i], j + f[j] - i) : 1;
        while (i + f[i] < n && i - f[i] >= 0 && check(s[i + f[i]], s[i - f[i]])) ++f[i];
        if (i + f[i] > j + f[j]) {
            for (int k = std::max(i, j + f[j]); k < i + f[i]; ++k) {
                auto [l, r] = std::array { 2 * i - k , k };
            }
            j = i;
        }
        auto [l, r] = std::array { i - f[i] + 1, i + f[i] - 1 };
    }
}