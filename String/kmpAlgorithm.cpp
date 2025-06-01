#include <bits/stdc++.h>

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