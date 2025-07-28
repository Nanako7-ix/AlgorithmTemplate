// https://qoj.ac/contest/1799/problem/9372
#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

void Thephix() {
    int n;
    cin >> n;
    vector<int> a(n), k(n);
    vector<int> fail(n), up(n + 1);
    i64 ans = 0, tot = 0;
    for (int i = 0, j = 0; i < n; ++i) {
        int s, x;
        cin >> s >> x >> k[i];
        a[i] = s = (s + ans) % n;
        if (i == 0 || s == a[0]) {
            tot += k[i];
        }
        if (i != 0) {
            up[i] = a[i] == a[j] ? up[j] : j;
            for (int u = up[i]; u; u = a[u] == s ? up[u] : fail[u - 1]) {
                if (a[u] == s) continue;
                tot -= k[i - u];
            }
            while (j && a[i] != a[j]) j = fail[j - 1];
            fail[i] = j += (a[i] == a[j]);
        }
        ans += tot * x;
        cout << ans << "\n";
    }
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
