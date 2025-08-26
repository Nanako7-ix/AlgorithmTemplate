#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

std::vector<int> Manacher(const std::string& t) {
    std::string s = "#";
    for (auto c : t) s += c, s += '#';

    int n = s.size();
    std::vector<int> d(n);
    for (int i = 0, j = 0; i < n; ++i) {
        d[i] = i < j + d[j] ? std::min(d[2 * j - i], j + d[j] - i) : 1;
        while (i + d[i] < n && i - d[i] >= 0 && s[i + d[i]] == s[i - d[i]]) ++d[i];
        if (i + d[i] > j + d[j]) j = i;
    }
    return d;
}

void Thephix() {
    int n;
    string s;
    cin >> n >> s;
    for (int i = 0; i < n; i += 2) {
        s[i] ^= 1;
    }

    i64 ans = 0;
    auto d = Manacher(s);
    for (int i = 0; i < (int) d.size(); i += 2) {
        ans += d[i] / 2;
    }
    cout << ans << "\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}