#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int N = 30;
using node = array<int, 3>;

void Thephix() {
    int n, k;
    cin >> n >> k;

    int ans = n + 1;
    vector<node> tr(2);
    for (int i = 1; i <= n; ++i) {
        int a; cin >> a;
        for (int j = N, p = 1; j >= 0; --j) {
            int x = a >> j & 1;
            if (tr[p][x] == 0) {
                tr[p][x] = tr.size();
                tr.push_back({});
            }
            p = tr[p][x];
            tr[p][2] = max(tr[p][2], i);
        }
        for (int j = 1; j < (int) tr.size(); ++j) {
            auto [l, r, dp] = tr[j];
        }
        for (int j = N, p = 1; j >= 0; --j) {
            int x = k >> j & 1;
            if (x == 1) {
                p = tr[p][(a >> j & 1) ^ 1];
            } else {
                if (tr[p][(a >> j & 1) ^ 1]) {
                    ans = min(ans, i - tr[tr[p][(a >> j & 1) ^ 1]][2] + 1);
                }
                p = tr[p][a >> j & 1];
            }
            if (p == 0) break;
            if (j == 0) ans = min(ans, i - tr[p][2] + 1);
        }
    }
    cout << (ans == n + 1 ? -1 : ans) << "\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}
