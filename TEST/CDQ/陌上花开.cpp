#include <bits/stdc++.h>

#define x(v) std::get<0> (v)
#define y(v) std::get<1> (v)
#define z(v) std::get<2> (v)
template<typename T1, typename T2, typename T3>
struct CDQ {
    using T = std::tuple<T1, T2, T3>;
    std::vector<std::tuple<T1, T2, T3>> a;

    CDQ () {
        init();
    }

    void init () {
        a.clear();
    }

    void add (const T1& x, const T2& y, const T3& z) {
        a.emplace_back(x, y, z);
    }

    template<typename Func>
    void work (Func&& op) {
        std::stable_sort(a.begin(), a.end());
        std::vector<std::pair<T, int>> b;
        for (auto x : a) {
            if (b.empty() || b.back().first != x) {
                b.emplace_back(x, 1);
            } else {
                b.back().second++;
            }
        }
        dfs(b.begin(), b.end(), op);
    }

    template<typename Func, typename Iterator = std::vector<std::pair<T, int>>::iterator>
    void dfs (const Iterator& l, const Iterator& r, Func&& op) {
        int len = r - l;
        if (len == 1) return;
        int m = len >> 1;
        dfs(l, l + m, op);
        dfs(l + m, r, op);
        
    }
};
#undef x(v)
#undef y(v)
#undef z(v)

void solve() {
    int n, k;
    std::cin >> n >> k;

    CDQ<int, int, int> cdq;
    std::map<std::tuple<int, int, int>, int> cnt;
    for (int i = 1; i <= n; ++i) {
        int x, y, z;
        std::cin >> x >> y >> z;
        cdq.add(x, y, z);
    }

    std::map<std::tuple<int, int, int>, int> f;
    cdq.work([&](std::tuple<int, int, int> x, int y) {
        f[x] += y;
    });

    for (auto& [x, y] : f) {
        y -= (cnt[x] * (cnt[x] - 1)) / 2;
        y += cnt[x] - 1;
    }

    for (int i = 1; i <= n; ++i) {

    }
}

int main () {
    std::cin.tie(0), std::cout.tie(0);
    std::ios::sync_with_stdio(false);

    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}