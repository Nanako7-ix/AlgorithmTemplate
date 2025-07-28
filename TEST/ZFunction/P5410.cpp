#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

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

void Thephix() {
    string a, b;
    cin >> a >> b;

    auto z = ZFunction(b);

    i64 ans = 0;
    for (int i = 0; i < (int) b.size(); ++i) {
        ans ^= 1LL * (i + 1) * (z[i] + 1);
    }
    cout << ans << "\n";

    z = ZFunction(b + '$' + a);
    ans = 0;
    for (int i = 0; i < (int) a.size(); ++i) {
        ans ^= 1LL * (i + 1) * (z[i + b.size() + 1] + 1);
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