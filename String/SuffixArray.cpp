#include <bits/stdc++.h>
using namespace std;

auto SuffixArray(const string& s) {
    int n = s.size();
    vector<int> sa(n + 1), rk(n + 1);
    iota(sa.begin() + 1, sa.end(), 1);
    sort(sa.begin() + 1, sa.end(), [&](int x, int y) {
        return s[x - 1] < s[y - 1];
    });

    rk[sa[1]] = 1;
    for (int i = 1; i < n; ++i) {
        rk[sa[i + 1]] = rk[sa[i]] + (s[sa[i + 1] - 1] != s[sa[i] - 1]);
    }
    
    vector<int> tmp(n + 1), cnt(n + 1);
    for (int k = 1; rk[sa[n - 1]] != n; k <<= 1) {
        // 先按照 [k + 1, 2k] 这个区间排序
        for (int i = n - k + 1, j = 1; i <= n; ++i, ++j) {
            tmp[j] = i;
        }
        for (int i = 1, j = k; i <= n; ++i) {
            if (sa[i] <= k) continue;
            tmp[++j] = sa[i] - k;
        }
        // 然后对 [1, k] 这个区间进行 stable_sort
        // 使用桶排序，当然也可以直接 stable_sort
        for (int i = 1; i <= n; ++i) {
            cnt[rk[i]]++;
        }
        for (int i = 1; i < rk[n]; ++i) {
            cnt[i + 1] += cnt[i];
        }
        for (int i = n; i >= 1; --i) {
            sa[cnt[rk[tmp[i]]]--] = tmp[i];
        }
        // 然后再计算一下 rk，顺便把 cnt 清空一下
        swap(rk, tmp);
        rk[sa[1]] = 1, cnt[tmp[sa[n]]] = 0;
        for (int i = 1; i < n; ++i) {
            cnt[tmp[sa[i]]] = 0;
            rk[sa[i + 1]] = rk[sa[i]] + (
                tmp[sa[i + 1]] != tmp[sa[i]] ||
                sa[i] + k - 1 == n ||
                tmp[sa[i + 1] + k] != tmp[sa[i] + k]
            );
        }
    }
    vector<int> height(n);

    return array {move(sa), move(rk), move(height)};
}
