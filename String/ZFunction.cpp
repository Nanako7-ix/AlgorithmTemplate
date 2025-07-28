#include <bits/stdc++.h>

auto ZFunction(std::string s) {
    int n = s.size();
    std::vector<int> z(n);
    z[0] = n;
    for (int i = 1, j = 1; i < n; ++i) {
        z[i] = std::max(0, std::min(j + z[j] - i, z[i - j]));
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
        if (i + z[i] > j + z[j]) j = i;
    }
    return z;
}
