#include <bits/stdc++.h>

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