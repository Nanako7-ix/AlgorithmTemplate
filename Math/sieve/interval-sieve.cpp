#include <bits/stdc++.h>

using i64 = long long;

// 你需要预处理出 根号范围内的素数
std::vector<int> P;

std::vector<int> interval_sieve(i64 l, i64 r) {
    assert (l + 1 <= r);
    std::vector<int> ok(r - l + 1, 1);
    if (l == 1) ok[0] = 0;
    for (i64 p : P) {
        i64 s = std::max(p * p, (l + p - 1) / p * p);
        for (i64 i = s; i <= r; i += p) {
            ok[i - l] = 0;
        }
    }
    return ok;
}