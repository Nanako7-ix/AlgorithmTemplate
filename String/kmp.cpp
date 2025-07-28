#include <bits/stdc++.h>

auto getFail (const std::string& s) {
    int n = s.size();
    std::vector<int> fail(n + 1);
    for (int i = 1, j = 0; i < n; ++i) {
        while (j && s[i] != s[j]) j = fail[j];
        fail[i + 1] = j += (s[i] == s[j]);
    }
    return fail;
}
